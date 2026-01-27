import React, { useState } from 'react';
import Keyboard from './Keyboard';
import { audioService } from '../services/AudioService';
import { Preset } from '../../../common/types/Preset';
import { Note } from '../types/Notes';
import '../styles/Synthesizer.css';

interface PresetParams {
  waveform: 'sine' | 'square' | 'sawtooth' | 'triangle' | 'noise';
  cutoff: number;
  resonance: number;
  attack: number;
  decay: number;
  sustain: number;
  release: number;
  volume: number;
  reverb: number;
  delay: number;
  chorus: number;
  pitch_bend: number;
  modulation: number;
}

const Synthesizer: React.FC = () => {
  const [frequency, setFrequency] = useState<number>(440);
  const [params, setParams] = useState<PresetParams>({
    waveform: 'sine',
    cutoff: 1000,
    resonance: 1,
    attack: 0.1,
    decay: 0.3,
    sustain: 0.7,
    release: 0.5,
    volume: 0.3,
    reverb: 0.25,
    delay: 0.15,
    chorus: 0.35,
    pitch_bend: 0.1,
    modulation: 0.2,
  });

  const [isPlaying, setIsPlaying] = useState(false);

  const handleParamChange = (param: keyof PresetParams, value: number | string) => {
    setParams((prevParams) => ({
      ...prevParams,
      [param]: value,
    }));
  };

  const handlePlayNote = () => {
    if (!isPlaying) {
      audioService.playNote(params as Preset, Note.A4, 2);
      setIsPlaying(true);
      setTimeout(() => setIsPlaying(false), (2 + params.release) * 1000);
    }
  };

  const handleStopNote = () => {
    audioService.stopNote();
    setIsPlaying(false);
  };

  const handleSavePreset = () => {
    console.log('Saving preset:', params);
    // TODO: Send to backend
  };

  return (
    <div>
      <h2>Oscillator</h2>
      <div className="waveform-selector">
        <label>Waveform</label>
        <select
          value={params.waveform}
          onChange={(e) =>
            handleParamChange(
              'waveform',
              e.target.value as
                | 'sine'
                | 'square'
                | 'sawtooth'
                | 'triangle'
                | 'noise'
            )
          }
          className="waveform-select"
        >
          <option value="sine">Sine</option>
          <option value="square">Square</option>
          <option value="sawtooth">Sawtooth</option>
          <option value="triangle">Triangle</option>
          <option value="noise">Noise</option>
        </select>
      </div>

      <Keyboard params={params as Preset} startOctave={4} octaveCount={4} />

      <div className="synthesizer-controls">
        <button
          className={`btn btn-play ${isPlaying ? 'active' : ''}`}
          onClick={handlePlayNote}
          disabled={isPlaying}
        >
          {isPlaying ? 'Playing...' : '▶ Play Note'}
        </button>
        <button
          className="btn btn-stop"
          onClick={handleStopNote}
          disabled={!isPlaying}
        >
          ⏹ Stop
        </button>
        <button className="btn btn-save" onClick={handleSavePreset}>
          💾 Save Preset
        </button>
      </div>
    </div>
  );
};

export default Synthesizer;
