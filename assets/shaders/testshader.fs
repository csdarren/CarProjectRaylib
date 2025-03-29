#version 330

// Input from vertex shader
in vec3 fragPosition;
in vec4 fragColor;
in vec3 fragNormal;
in vec4 fragPosLightSpace;  // Position in light space

// Uniform values
uniform vec4 colDiffuse;
uniform vec4 ambient;
uniform vec3 viewPos;

// Shadow map
uniform sampler2D shadowMap;  // Depth texture from light’s perspective

#define MAX_LIGHTS 4
#define LIGHT_DIRECTIONAL 0
#define LIGHT_POINT 1

struct Light {
    int enabled;
    int type;
    vec3 position;
    vec3 target;
    vec4 color;
};

uniform Light lights[MAX_LIGHTS];

// Function to calculate shadow factor
float ShadowCalculation(vec4 fragPosLightSpace)
{
    // Convert from clip space to NDC to texture space
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    // Get closest depth value from shadow map
    float closestDepth = texture(shadowMap, projCoords.xy).r;

    // Current depth of fragment from light's perspective
    float currentDepth = projCoords.z;

    // Shadow bias to prevent artifacts
    float bias = 0.005;

    // If the fragment is in shadow, reduce brightness
    float shadow = currentDepth - bias > closestDepth ? 0.3 : 1.0;

    return shadow;
}

out vec4 finalColor;  // Define the final color output

void main()
{
    vec3 normal = normalize(fragNormal);
    vec3 viewD = normalize(viewPos - fragPosition);
    vec3 lightDot = vec3(0.0);
    vec3 specular = vec3(0.0);

    // Compute shadow factor
    float shadowFactor = ShadowCalculation(fragPosLightSpace);

    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        if (lights[i].enabled == 1)
        {
            vec3 light = vec3(0.0);

            if (lights[i].type == LIGHT_DIRECTIONAL)
            {
                light = -normalize(lights[i].target - lights[i].position);
            }

            if (lights[i].type == LIGHT_POINT)
            {
                light = normalize(lights[i].position - fragPosition);
            }

            float NdotL = max(dot(normal, light), 0.0);
            lightDot += lights[i].color.rgb * NdotL * shadowFactor;

            float specCo = 0.0;
            if (NdotL > 0.0)
                specCo = pow(max(0.0, dot(viewD, reflect(-light, normal))), 16.0);
            
            specular += specCo;
        }
    }

    // Combine lighting and diffuse/specular components
    finalColor = fragColor * ((colDiffuse + vec4(specular, 1.0)) * vec4(lightDot, 1.0));
    finalColor += fragColor * (ambient / 10.0) * colDiffuse;

    // Gamma correction
    finalColor = pow(finalColor, vec4(1.0 / 2.2));
}