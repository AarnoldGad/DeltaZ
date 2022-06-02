#version 330

out vec4 FragColor;

in float iValue;

uniform float maxValue;
uniform float minValue;
uniform bool renderBlack;

void main()
{
   if (renderBlack)
      FragColor = vec4(0.0, 0.0, 0.0, 1.0);
   else
   {
      float valueSpan = maxValue - minValue;
      float value = iValue - minValue;
      float mixer = value / valueSpan;
      if (mixer > 0.75)
         FragColor = vec4(1.0, 4.0 - 4 * mixer, 0.0, 1.0);
      else if (mixer > 0.5)
         FragColor = vec4(4.0 * mixer - 2.0, 1.0, 0.0, 1.0);
      else if (mixer > 0.25)
         FragColor = vec4(0.0, 1.0, 2.0 - 4.0 * mixer, 1.0);
      else
         FragColor = vec4(0.0, 4.0 * mixer, 1.0, 1.0);
   }
}
