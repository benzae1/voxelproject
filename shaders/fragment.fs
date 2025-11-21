#version 460 core

in vec3 vColor;       // From vertex shader
out vec4 FragColor;   // Final pixel color

void main()
{
    FragColor = vec4(vColor, 1.0);
}
