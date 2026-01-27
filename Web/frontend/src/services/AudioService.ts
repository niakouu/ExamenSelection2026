import { Preset } from '../../../common/types/Preset';
import { Note } from '../types/Notes';

interface ActiveNote {
  oscillator: OscillatorNode;
  lfoOscillator: OscillatorNode;
  gainNode: GainNode;
  filter: BiquadFilterNode;
  dryGain: GainNode;
  wetGain: GainNode;
  convolver: ConvolverNode;
  delayNode: DelayNode;
  delayFeedback: GainNode;
  lfoGain: GainNode;
  stopTimeout: NodeJS.Timeout;
}

class AudioService {
  private audioContext: AudioContext | null = null;
  private activeNotes: Set<ActiveNote> = new Set();
  private convolver: ConvolverNode | null = null;
  private isPlaying: boolean = false;

  constructor() {
    this.initAudioContext();
  }

  private initAudioContext(): void {
    if (!this.audioContext) {
      this.audioContext = new (window.AudioContext || (window as any).webkitAudioContext)();
    }

  }

  private createReverbImpulse(): AudioBuffer {
    const ctx = this.audioContext!;
    const rate = ctx.sampleRate;
    const length = rate * 2;
    const impulse = ctx.createBuffer(2, length, rate);
    const left = impulse.getChannelData(0);
    const right = impulse.getChannelData(1);

    for (let i = 0; i < length; i++) {
      left[i] = (Math.random() * 2 - 1) * Math.pow(1 - i / length, 2);
      right[i] = (Math.random() * 2 - 1) * Math.pow(1 - i / length, 2);
    }
    return impulse;
  }

  public playNote(params: Preset, frequency: Note, duration: number): void {
    if (!this.audioContext) {
      this.initAudioContext();
    }
    const ctx = this.audioContext!;

    // Create a new oscillator and effect chain for this note
    const oscillator = ctx.createOscillator();
    const gainNode = ctx.createGain();
    const filter = ctx.createBiquadFilter();
    const dryGain = ctx.createGain();
    const wetGain = ctx.createGain();
    const convolver = ctx.createConvolver();
    const delayNode = ctx.createDelay(5);
    const delayFeedback = ctx.createGain();
    const lfoOscillator = ctx.createOscillator();
    const lfoGain = ctx.createGain();

    // Set up reverb
    convolver.buffer = this.createReverbImpulse();

    // Connect audio graph for this note
    oscillator.connect(filter);
    filter.connect(gainNode);

    gainNode.connect(dryGain);
    gainNode.connect(wetGain);

    dryGain.connect(ctx.destination);

    wetGain.connect(convolver);
    convolver.connect(delayNode);
    delayNode.connect(delayFeedback);
    delayFeedback.connect(delayNode);
    delayNode.connect(ctx.destination);

    // Connect LFO to oscillator frequency
    lfoOscillator.connect(lfoGain);
    lfoGain.connect(oscillator.frequency);

    const now = ctx.currentTime;

    // Set oscillator parameters
    oscillator.type = params.waveform as OscillatorType;
    oscillator.frequency.setValueAtTime(frequency.valueOf(), now);

    // Set up LFO (Low Frequency Oscillator) for modulation
    lfoOscillator.type = 'sine';
    lfoOscillator.frequency.setValueAtTime(5, now); // 5 Hz LFO rate
    lfoGain.gain.setValueAtTime(params.pitch_bend * 10, now); // Pitch bend modulation depth

    // Set filter parameters
    filter.type = 'lowpass';
    filter.frequency.setValueAtTime(params.cutoff, now);
    filter.Q.setValueAtTime(params.resonance, now);

    // Apply modulation to filter cutoff
    if (params.modulation > 0) {
      const modulationAmount = params.modulation * params.cutoff * 0.3;
      filter.frequency.setValueAtTime(params.cutoff + modulationAmount, now);
    }

    // ADSR Envelope
    gainNode.gain.setValueAtTime(0, now);
    gainNode.gain.linearRampToValueAtTime(params.volume, now + params.attack);
    gainNode.gain.linearRampToValueAtTime(
      params.sustain * params.volume,
      now + params.attack + params.decay
    );
    gainNode.gain.linearRampToValueAtTime(0, now + duration + params.release);

    // Effects
    dryGain.gain.setValueAtTime(1 - params.reverb, now);
    wetGain.gain.setValueAtTime(params.reverb, now);

    delayNode.delayTime.setValueAtTime(params.delay, now);
    delayFeedback.gain.setValueAtTime(params.delay * 0.3, now);

    // Start oscillators
    oscillator.start(now);
    lfoOscillator.start(now);

    // Create the active note object
    const stopTimeout = setTimeout(() => {
      this.stopNoteInstance(activeNote);
    }, (duration + params.release) * 1000);

    const activeNote: ActiveNote = {
      oscillator,
      lfoOscillator,
      gainNode,
      filter,
      dryGain,
      wetGain,
      convolver,
      delayNode,
      delayFeedback,
      lfoGain,
      stopTimeout,
    };

    this.activeNotes.add(activeNote);
    this.isPlaying = this.activeNotes.size > 0;
  }

  private stopNoteInstance(activeNote: ActiveNote): void {
    if (this.audioContext) {
      const now = this.audioContext.currentTime;
      activeNote.oscillator.stop(now);
      activeNote.lfoOscillator.stop(now);
      activeNote.oscillator.disconnect();
      activeNote.lfoOscillator.disconnect();
      clearTimeout(activeNote.stopTimeout);
      this.activeNotes.delete(activeNote);
      this.isPlaying = this.activeNotes.size > 0;
    }
  }

  public stopNote(): void {
    // Stop all active notes
    const notesToStop = Array.from(this.activeNotes);
    notesToStop.forEach((note) => this.stopNoteInstance(note));
  }

  public updateFrequency(frequency: number): void {
    if (this.audioContext) {
      this.activeNotes.forEach((note) => {
        note.oscillator.frequency.setTargetAtTime(
          frequency,
          this.audioContext!.currentTime,
          0.01
        );
      });
    }
  }

  public updateFilter(cutoff: number, resonance: number): void {
    if (this.audioContext) {
      this.activeNotes.forEach((note) => {
        note.filter.frequency.setTargetAtTime(cutoff, this.audioContext!.currentTime, 0.01);
        note.filter.Q.setTargetAtTime(resonance, this.audioContext!.currentTime, 0.01);
      });
    }
  }

  public updateVolume(volume: number): void {
    if (this.audioContext) {
      this.activeNotes.forEach((note) => {
        note.gainNode.gain.setTargetAtTime(volume, this.audioContext!.currentTime, 0.01);
      });
    }
  }

  public isAudioPlaying(): boolean {
    return this.isPlaying;
  }
}

export const audioService = new AudioService();
