#version 330 core

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec3 inCol;
out vec4 chCol;

// Uniforme za pomeraj dugmeta
uniform float uX; 
uniform float uY;
uniform float uScaleX;
uniform float uScaleY;

void main()
{
    vec2 scaledPos = inPos * vec2(uScaleX,uScaleY);//mijenja sirinu loading bara
    // Postavlja poziciju na (inPos.x + uX, inPos.y + uY)
    gl_Position = vec4(scaledPos.x + uX, scaledPos.y + uY, 0.0, 1.0);
    chCol = vec4(inCol, 1.0);
}