import React, { useState } from 'react';
import { Note } from '../types/Notes';
import { audioService } from '../services/AudioService';
import { Preset } from '../../../common/types/Preset';
import '../styles/Keyboard.css';

interface KeyboardProps {
  params: Preset;
  startOctave?: number;
  octaveCount?: number;
}

interface KeyInfo {
  name: string;
  note: Note;
  isBlack: boolean;
}

const Keyboard: React.FC<KeyboardProps> = ({
  params,
  startOctave = 4,
  octaveCount = 4,
}) => {
  const [activeKeys, setActiveKeys] = useState<Set<string>>(new Set());

  return (
    <div className="keyboard-container">
      <h3>Keyboard - Octaves {startOctave} to {startOctave + octaveCount - 1}</h3>
    </div>
  );
};

export default Keyboard;
