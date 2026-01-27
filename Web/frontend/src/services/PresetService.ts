import { backendService } from './BackendService';

export class PresetService {
  async getAllPresets(): Promise<any[]> {
    return backendService.get('/presets');
  }

  async getPresetById(id: number): Promise<any> {
    return backendService.get(`/presets/${id}`);
  }

  async getPresetCount(): Promise<{ count: number; atvailableIds: number[] }> {
    return backendService.get('/presets/count');
  }
}

export const presetService = new PresetService();
