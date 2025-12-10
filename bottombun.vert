#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

uniform float uX;
uniform float uY;
uniform float uS;

out vec2 TexCoord;

void main()
{
    vec2 pos = aPos * uS + vec2(uX, uY);
    gl_Position = vec4(pos, 0.0, 1.0);
    TexCoord = aTex;
}
