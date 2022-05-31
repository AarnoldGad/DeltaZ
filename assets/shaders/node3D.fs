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
      if (iValue >= 0)
      {
         float mixer = iValue / maxValue;
         if (mixer > 0.5)
            FragColor = vec4(1.0, 2.0 - mixer * 2.0, 0.0, 1.0);
         else
            FragColor = vec4(mixer * 2.0, 1.0, 0.0, 1.0);
      }
      else if (iValue < 0.0)
      {
         float mixer = iValue / minValue;
         if (mixer > 0.5)
            FragColor = vec4(0.0, 2.0 - mixer * 2.0, 1.0, 1.0);
         else
            FragColor = vec4(0.0, 1.0, mixer * 2.0, 1.0);
      }
   }
}
