#version 330 core

struct Material {
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    float Ns;
    float d;
};

uniform Material material;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform sampler2D texture1;
uniform bool isTexture;
uniform bool isGradient;
uniform vec3 gradientColor;
uniform float gradientFactor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

void main() {
    vec3 ambient = material.Ka;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * material.Kd * lightColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Ns);
    vec3 specular = spec * material.Ks * lightColor;

    vec3 result = ambient + diffuse + specular;

    if (isGradient) {
        vec3 mixedColor = mix(result, gradientColor, gradientFactor);
        result = mixedColor;
    }

    if (isTexture)
        FragColor = texture(texture1, TexCoord);
    else
        FragColor = vec4(result, material.d);
}
