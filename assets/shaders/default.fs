#version 330

out vec4 FragColor;

in vec4 iColor;
in vec2 iTexCoord;

uniform float uTime;
uniform sampler2D tex0;

void main()
{
   vec4 texColor = texture(tex0, iTexCoord);
   FragColor = vec4(texColor.rgb * iColor.rgb, texColor.a);
}
