import React from 'react';
import Synthesizer from './components/Synthesizer';
import './App.css';
import { PresetService } from './services/PresetService';

function App() {
  const pre = new PresetService();
  pre.getAllPresets().then((data) => {
    console.log('Presets from backend:', data);
  });
  return (
    <div className="App">
      <Synthesizer />
    </div>
  );
}

export default App;
