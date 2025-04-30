#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform sampler2D texture_diffuse1;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-lightDirection);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 light = (ambient + diffuse);
    FragColor = vec4(light, 1.0f) * texture(texture_diffuse1, TexCoords);
}