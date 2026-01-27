#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

void main()
{
    // TODO: Implement Phong shading model here
    vec3 colorA = lightColor; 


    vec3 ambient = vec3(0.1) * colorA;
    vec3 diffuse = vec3(1.0);
    vec3 specular = vec3(1.0);
    

    vec3 result = ambient + diffuse + specular;
    result = clamp(result, 0.0, 1.0); 

    FragColor = vec4(result, 1.0);
}