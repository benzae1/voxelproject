#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord; // new

out vec3 vColor;
out vec2 TexCoord; // pass to fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0);
    vColor = aColor;
    TexCoord = aTexCoord;
}
