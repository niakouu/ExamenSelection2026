#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform float time;
uniform sampler2D texture1;

void main()
{
    // TODO: Finish the fragment shader implementation
    

    vec3 norm = normalize(Normal);
    
    vec3 finalColor = vec3(1.0, 0.0, 0.0);
    FragColor = vec4(finalColor, 1.0);
}
