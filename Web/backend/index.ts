import express from 'express';
import dotenv from 'dotenv';

dotenv.config();

import { setupPresetsRoutes } from './routes/presets/PresetsRoute';

const app: express.Application = express();

const port: number = parseInt(process.env.PORT || '3030', 10);

app.use((req, res, next) => {
  res.header('Access-Control-Allow-Origin', '*');
  res.header('Access-Control-Allow-Methods', 'GET, POST, PUT, PATCH, DELETE, OPTIONS');
  res.header('Access-Control-Allow-Headers', 'Origin, X-Requested-With, Content-Type, Accept');
  
  if (req.method === 'OPTIONS') {
    res.sendStatus(200);
  } else {
    next();
  }
});

app.use(express.json());

app.get('/', (_req, res) => {
    res.send('Welcome try the /presets endpoint!');
});

setupPresetsRoutes(app);



app.listen(port, () => {
    console.log(`TypeScript with Express 
         http://localhost:${port}/`);
});