#version 330

out vec4 FragColor;

in vec4 iColor;
in vec2 iTexCoord;

uniform float uTime;
uniform sampler2D atlas;

void main()
{
   vec4 texColor = texture(atlas, iTexCoord);
   FragColor = vec4(0.0, 0.0, 0.0, texColor.r);
}
