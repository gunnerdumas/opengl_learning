#version 330 core
layout (location = 0) in vec2 vertex;
layout (location = 1) in vec3 aColor;

out vec2 TexCoords;
out vec3 ourColor;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoords = vertex.zw;
    gl_Position = projection*model*vec4(aPos, 0.0, 1.0);
    ourColor = aColor;
}
