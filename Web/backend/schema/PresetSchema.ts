import { z } from 'zod';

export const PresetSchema = z.object({
  id: z.number().optional(),
  name: z.string().min(1),
  description: z.string().nullable().optional(),
  waveform: z.enum(['sine', 'square', 'sawtooth', 'triangle', 'custom']),
  cutoff: z.number(),
  resonance: z.number(),
  attack: z.number(),
  decay: z.number(),
  sustain: z.number(),
  release: z.number(),
  volume: z.number(),
  reverb: z.number(),
  delay: z.number(),
  chorus: z.number(),
  pitch_bend: z.number(),
  modulation: z.number(),
  created_at: z.string().optional(),
  updated_at: z.string().optional(),
});