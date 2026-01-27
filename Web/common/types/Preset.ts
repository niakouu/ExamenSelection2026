export interface Preset {
    id: number;
    name: string;
    description: string | null;
    waveform: 'sine' | 'square' | 'sawtooth' | 'triangle' | 'custom';
    // Filters
    cutoff: number;
    resonance: number;
    // Envelope
    attack: number;
    decay: number;
    sustain: number;
    release: number;
    // Effects
    volume: number;
    reverb: number;
    delay: number;
    chorus: number;
    // Modulation
    pitch_bend: number;
    modulation: number;
    // Timestamps
    created_at: string;
    updated_at: string;
}
