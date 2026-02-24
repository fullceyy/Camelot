#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vColor;
out vec3 fragPos;

void main()
{
    vec4 worldPos = projection * view * model * vec4(aPos, 1.0);
    fragPos = worldPos.xyz;
    gl_Position = worldPos;
    vColor = aColor;
};