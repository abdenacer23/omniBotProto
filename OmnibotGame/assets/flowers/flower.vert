#version 150
uniform mat4 ciModelMatrix;
uniform mat4 ciViewMatrix;

in vec4 ciPosition;
in vec3 ciNormal;
in vec3 ciTangent;

out vec3 flat_in;
out vec3 dir_in;
void main()
{
  
    gl_Position = ciPosition;
   dir_in=ciNormal;
    flat_in =ciTangent;
   // vvShadowCoord	= ( biasMatrix * uShadowMatrix * ciModelMatrix ) * ciPosition;
   //flatD =ciTexCoord1;
    //text =ciTexCoord0;
}
