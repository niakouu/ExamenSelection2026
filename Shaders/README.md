# Épreuve de Shaders! 

## Installation

Dépendance pour compiler le projet:
- Cmake

Pour installer les dépendances sur Ubuntu/Debian:
```bash
sudo apt-get install build-essential cmake
```

Sur MacOs:
```bash
brew install cmake
```

Sur Arch linux:
```bash
sudo pacman -S base-devel cmake
```

Pour compiler le projet, il suffit d'exécuter les commandes suivantes dans le dossier `Shaders`:
```bash
mkdir -p build/ && cd build/
cmake .. # Si tu as des erreurs de version de cmake, essaie avec le flag -DCMAKE_POLICY_VERSION_MINIMUM=3.5 
make -j$(nproc)

./cs_exam_shaders
```


# Tâche à faire 

## 1. Shaders pour la vague

1. Implémenter le vertex shader dans le fichier [wavePlane.vs.glsl](./shaders/wavePlane/wavePlane.vs.glsl)

Ce vertex shader prend des uniforms lock en entrée, cette logique est déjà faite pour vous. 
```glsl
uniform float waveAmplitude;
uniform float waveFrequency;
uniform float waveSpeed;
```

Vous devez implémenter la logique qui change la hauteur du fragment selon la position. 

2. Finir l'implémentation du fragment shader: [wavePlane.fs.glsl](./shaders/wavePlane/wavePlane.fs.glsl)

Ce shader prend en entrée les uniforms lock suivants:
```glsl
uniform vec3 waveColor1;  
uniform vec3 waveColor2;  
uniform float waveAmplitude;
```

Vous devez implémenter le meilleur shader de vague!

## 2. Créer un shader fluorescent pour le cube

Vous devez créer un shader qui permet au cube de briller, comme s'il était fluorescent.

La couleur et les paramètre des effets fluorescent doivent pouvoir être changer à l'aide d'une interface utilisant la librarie `ImGui`. 

Il suffit d'ajouter du code dans la fonction `renderCustomImGui()` dans la classe `Cube` pour créer une petite interface custom. 

Les fichiers à modifier se trouvent dans [shaders/cube/](./shaders/cube/):
- [cube.vs.glsl](./shaders/cube/cube.vs.glsl) - Vertex shader
- [cube.fs.glsl](./shaders/cube/cube.fs.glsl) - Fragment shader

Et pour la classe [Cube](./src/mesh/cube/cube.cpp)

### Idées pour un effet fluorescent:

1. **Effet de bordure lumineuse (Fresnel Glow)**
   - Utiliser l'effet Fresnel pour rendre les bords plus lumineux
   - Calculer l'angle entre la normale et la direction de la caméra
   - Intensifier la couleur aux bordures: `float rim = 1.0 - dot(normal, viewDir)`
   - Appliquer une puissance pour contrôler l'intensité: `pow(rim, 3.0)`

2. **Pulsation temporelle**
   - Utiliser l'uniform `time` pour faire varier l'intensité
   - `float pulse = sin(time * speed) * 0.5 + 0.5`
   - Multiplier la couleur fluorescente par le pulse

3. **Couleurs vives saturées**
   - Utiliser des couleurs néon: cyan (0, 1, 1), magenta (1, 0, 1), vert fluo (0, 1, 0.3)
   - Augmenter l'intensité au-delà de 1.0 pour un effet HDR: `color * 2.0` ou plus

4. **Combinaison d'effets**
   - Combiner Fresnel + pulsation: `vec3 glow = neonColor * rim * pulse * intensity`
   - Ajouter un léger gradient de couleur basé sur la position
   - Optionnel: ajouter du bruit pour un effet plus organique

## 3. Implémenter Phong Shading

Vous devez compléter l'implémentation du fragment shader pour un phong shading dans le fichier [phong.fs.glsl](./shaders/phong/phong.fs.glsl).

Ce shader va seulement être utilisé dans la deuxième scène.

### Rappel sur le modèle de Phong

Le modèle de Phong combine trois composantes d'éclairage:

1. **Ambient (Ambiante)** - Lumière uniforme de base
   - Simule la lumière indirecte dans la scène

2. **Diffuse (Diffuse)** - Lumière directionnelle mate
   - Dépend de l'angle entre la normale et la direction de la lumière
   - Plus la surface fait face à la lumière, plus elle est éclairée


3. **Specular (Spéculaire)** - Reflets brillants
   - Simule les reflets brillants sur les surfaces
   - Dépend de l'angle entre la réflexion et la direction de vue

### Formule complète:

```glsl
vec3 result = (ambient + diffuse + specular) * objectColor;
```


### Uniforms déja implémenté:

```glsl
uniform vec3 lightPos;        // Position de la lumière
uniform vec3 viewPos;         // Position de la caméra
uniform vec3 lightColor;      // Couleur de la lumière
uniform vec3 objectColor;     // Couleur de l'objet
``` 