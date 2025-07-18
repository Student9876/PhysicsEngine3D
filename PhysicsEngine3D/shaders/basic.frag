#version 330 core

#define MAX_LIGHTS 8

struct Attenuation {
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    float innerCutoff;
    float outerCutoff;
};

struct Light {
    int type;           // 0 = directional, 1 = point, 2 = spot
    vec3 position;
    vec3 direction;
    vec3 color;
    float brightness;
    float intensity;
    bool enabled;
    
    Attenuation attenuation;
    SpotLight spotlight;
};

uniform Light lights[MAX_LIGHTS];
uniform int numLights;
uniform vec3 ambientLight;
uniform vec3 objectColor;
uniform vec3 viewPos;

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

vec3 calculateDirectionalLight(Light light, vec3 normal, vec3 viewDir) {
    if (!light.enabled) return vec3(0.0);
    
    vec3 lightDir = normalize(-light.direction);
    
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    
    // Combine results
    vec3 diffuse = light.color * diff * light.brightness * light.intensity;
    vec3 specular = light.color * spec * light.brightness * light.intensity * 0.5;
    
    return diffuse + specular;
}

vec3 calculatePointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    if (!light.enabled) return vec3(0.0);
    
    vec3 lightDir = normalize(light.position - fragPos);
    
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.attenuation.constant + 
                              light.attenuation.linear * distance + 
                              light.attenuation.quadratic * (distance * distance));
    
    // Combine results
    vec3 diffuse = light.color * diff * light.brightness * light.intensity;
    vec3 specular = light.color * spec * light.brightness * light.intensity * 0.5;
    
    diffuse *= attenuation;
    specular *= attenuation;
    
    return diffuse + specular;
}

vec3 calculateSpotLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    if (!light.enabled) return vec3(0.0);
    
    vec3 lightDir = normalize(light.position - fragPos);
    
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.attenuation.constant + 
                              light.attenuation.linear * distance + 
                              light.attenuation.quadratic * (distance * distance));
    
    // Spotlight (soft edges)
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.spotlight.innerCutoff - light.spotlight.outerCutoff;
    float intensity = clamp((theta - light.spotlight.outerCutoff) / epsilon, 0.0, 1.0);
    
    // Combine results
    vec3 diffuse = light.color * diff * light.brightness * light.intensity;
    vec3 specular = light.color * spec * light.brightness * light.intensity * 0.5;
    
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    
    return diffuse + specular;
}

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 result = ambientLight;
    
    // Calculate lighting for each light source
    for (int i = 0; i < numLights && i < MAX_LIGHTS; i++) {
        if (lights[i].type == 0) {
            // Directional light
            result += calculateDirectionalLight(lights[i], norm, viewDir);
        } else if (lights[i].type == 1) {
            // Point light
            result += calculatePointLight(lights[i], norm, FragPos, viewDir);
        } else if (lights[i].type == 2) {
            // Spot light
            result += calculateSpotLight(lights[i], norm, FragPos, viewDir);
        }
    }
    
    FragColor = vec4(result * objectColor, 1.0);
}