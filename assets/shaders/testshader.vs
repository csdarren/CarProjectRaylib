#version 330

// Input vertex attributes
in vec3 vertexPosition;
in vec3 vertexNormal;
in vec4 vertexColor;

// Input uniform values
uniform mat4 mvp;
uniform mat4 matModel;
uniform mat4 matNormal;

// Shadow mapping
uniform mat4 lightSpaceMatrix;  // Light projection * view * model matrix

// Output to fragment shader
out vec3 fragPosition;
out vec4 fragColor;
out vec3 fragNormal;
out vec4 fragPosLightSpace;  // Position in light space for shadow calculations

void main()
{
    fragPosition = vec3(matModel * vec4(vertexPosition, 1.0));
    fragColor = vertexColor;
    fragNormal = normalize(vec3(matNormal * vec4(vertexNormal, 1.0)));

    // Transform the fragment position into light space
    fragPosLightSpace = lightSpaceMatrix * vec4(fragPosition, 1.0);

    // Calculate final vertex position
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}