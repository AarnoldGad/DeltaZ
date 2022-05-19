#version 330

layout (location = 0) in vec2 vPos;
layout (location = 1) in float vValue;

uniform mat4 view;
uniform mat4 projection;

out float iValue;

void main()
{
   gl_Position = projection * view * vec4(vPos.xy, 0.0, 1.0);
   gl_PointSize = 5.0;
   iValue = vValue;
}
