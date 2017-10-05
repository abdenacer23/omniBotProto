#version 150

in vec3 vColor;
in vec3 vNormal;
in vec4 vShadowCoord;
in float r;
out vec4 outColor;



uniform sampler2DShadow uShadowMap;


float samplePCF3x3( vec4 sc )
{
    const int s = 1;
    
    float shadow = 0.0;
    shadow += textureProjOffset( uShadowMap, sc, ivec2(-s,-s) );
    shadow += textureProjOffset( uShadowMap, sc, ivec2(-s, 0) );
    shadow += textureProjOffset( uShadowMap, sc, ivec2(-s, s) );
    shadow += textureProjOffset( uShadowMap, sc, ivec2( 0,-s) );
    shadow += textureProjOffset( uShadowMap, sc, ivec2( 0, 0) );
    shadow += textureProjOffset( uShadowMap, sc, ivec2( 0, s) );
    shadow += textureProjOffset( uShadowMap, sc, ivec2( s,-s) );
    shadow += textureProjOffset( uShadowMap, sc, ivec2( s, 0) );
    shadow += textureProjOffset( uShadowMap, sc, ivec2( s, s) );
    return shadow/9.0;;
}

void main()
{
    
    vec4 ShadowCoord	= vShadowCoord / vShadowCoord.w;
    float Shadow		= 1.0;
    
    if ( ShadowCoord.z > -1 && ShadowCoord.z < 1 ) {
        Shadow = samplePCF3x3(ShadowCoord) ;
    }
    Shadow =clamp(Shadow,1.0,1.0);
  
    outColor = vec4( vColor*r*Shadow, 1.0);
   //outColor =vec4(vec3(r),1.0);
}
