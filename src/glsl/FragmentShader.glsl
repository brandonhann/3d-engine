#version 330 core

out vec4 FragColor;
in vec3 Normal;  // Normal of the vertex
in vec3 FragPos;  // Position of the fragment

uniform vec3 lightPos;  // Position of the light source
uniform vec4 lightColor;  // Color of the light source
uniform vec4 objectColor;  // Color of the object

void main()
{
    // Ambient
    float ambientStrength = 0.1f;
    vec4 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * lightColor;

    vec4 result = (ambient + diffuse) * objectColor;
    FragColor = result;
}