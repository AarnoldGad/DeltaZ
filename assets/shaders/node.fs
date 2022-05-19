#version 330

out vec4 FragColor;

in float iValue;

void main()
{
   FragColor = vec4(iValue, 0.0, 0.0, 1.0);
}
