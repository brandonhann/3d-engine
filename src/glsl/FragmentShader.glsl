#version 330 core
in vec3 Normal;  
in vec3 FragPos;  

out vec4 color;

uniform vec3 lightPos; 
uniform vec4 lightColor;
uniform vec4 objectColor;

void main()
{
    // Ambient
    float ambientStrength = 0.1; // You can adjust this value to get your desired effect
    vec4 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * lightColor;

    vec4 result = (ambient + diffuse) * objectColor;
    color = vec4(result.xyz, 1.0); // Assuming alpha value of 1.0
}
