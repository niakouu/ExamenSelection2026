import { Request, Response, Application } from 'express';
import { z } from 'zod';
import { PresetSchema } from '../../schema/PresetSchema';
import { presetService } from '../../services/PresetService';


export const setupPresetsRoutes = (app: Application): void => {
    
    app.get('/presets', getAllPresets);
    app.get('/presets/count', getPresetCount);
    app.get('/presets/:id', getPresetById);
    app.patch('/presets/:id', patchPreset);

    // TODO: Implement these routes
    app.post('/presets', postPreset);
    app.delete('/presets/:id', deletePreset);
};


export const getPresetById = (req: Request, res: Response): void => {
    const idParam = req.params.id;
    const id = parseInt(Array.isArray(idParam) ? idParam[0] : idParam, NaN);

    if (isNaN(id)) {
        res.status(400).json({ error: 'Invalid preset ID' });
        return;
    }

    const preset = presetService.getPresetById(id);

    if (!preset) {
        res.status(404).json({ error: `Preset with id ${id} not found` });
        return;
    }

    res.json(preset);
};

export const getAllPresets = (_req: Request, res: Response): void => {
    const presets = presetService.getAllPresets();
    res.json(presets);
};

export const getPresetCount = (_req: Request, res: Response): void => {
    const count = presetService.getPresetCount();
    res.json({ count, atvailableIds: presetService.getAvailableIds() });
};




export const patchPreset = (req: Request, res: Response): void => {
    try {
        const idParam = req.params.id;
        const id = parseInt(Array.isArray(idParam) ? idParam[0] : idParam, NaN);

        if (isNaN(id)) {
            res.status(400).json({ error: 'Invalid preset ID' });
            return;
        }

        const validatedData = PresetSchema.partial().parse(req.body);
        const success = presetService.updatePreset(id, { ...validatedData, updated_at: new Date().toISOString() });

        if (!success) {
            res.status(404).json({ error: `Preset with id ${id} not found` });
            return;
        }

        res.json({ message: `Preset with id ${id} updated successfully` });
    } catch (error) {
        if (error instanceof z.ZodError) {
            res.status(404).json({ 
                error: 'Data missing or invalid',
                details: error.errors
            });
            return;
        }

        res.status(500).json({ error: 'Internal server error' });
    }
}

export const postPreset = (req: Request, res: Response): void => {
    console.log("Not implemented yet");
    res.status(501).json({ error: 'Not implemented yet' });
};

export const deletePreset = (req: Request, res: Response): void => {
    console.log("Not implemented yet");
    res.status(501).json({ error: 'Not implemented yet' });
};