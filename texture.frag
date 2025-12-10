#version 330 core

in vec2 chTex;
out vec4 outCol;

uniform sampler2D uTex; // Uniforma za vezivanje teksture
uniform float uA;   //uniforma za kontrolu alfa kanala (providnost)

void main()
{
    vec4 texColor = texture(uTex, chTex);
    
    //outCol = texColor; 
    outCol = vec4(texColor.rgb, texColor.a * uA);
}