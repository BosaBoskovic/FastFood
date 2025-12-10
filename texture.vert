#version 330 core

layout(location = 0) in vec2 inPos;    // pozicija
layout(location = 1) in vec2 inTex;    // koordinate teksture

out vec2 chTex;

uniform float uX; // pomeranje po X
uniform float uY; // pomeranje po Y
uniform float uS; //skaliranje, ako se ne koristi 1.0 ce biti

void main()
{
    vec2 pos = inPos * uS + vec2(uX, uY);
    gl_Position = vec4(pos, 0.0, 1.0);
    chTex = inTex;
}