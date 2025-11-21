#version 460 core
in vec3 vColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1; // the texture

void main()
{
    FragColor = texture(texture1, TexCoord) * vec4(vColor, 1.0); // sample texture
}
