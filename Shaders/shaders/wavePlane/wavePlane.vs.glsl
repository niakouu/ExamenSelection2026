#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;
out float WaveHeight;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

uniform float waveAmplitude;
uniform float waveFrequency;
uniform float waveSpeed;

void main() {
    // TODO: Finish the vertex shader implementation
    // You need to create a realistic wave effect on the plane

    float wave1 = 0.3;
    float wave2 = 0.3;
    float wave3 = 0.3;
    
    float totalWave = wave1 + wave2 + wave3;
    
    vec3 displacedPos = aPos;
    displacedPos.y += totalWave;
    
    float dx = 1;

    float dz = 1;
    
    vec3 calculatedNormal = normalize(vec3(-dx, 1.0, -dz));
    
    FragPos = vec3(model * vec4(displacedPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * calculatedNormal;
    TexCoord = aTexCoord;
    WaveHeight = totalWave;
    
    gl_Position = projection * view * model * vec4(displacedPos, 1.0);
}
