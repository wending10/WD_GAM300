layout(location =0) in vec3 fragColor;
layout(location =1) in vec3 fragTexCoord;
layout(location =2) in vec3 fragPosWorld;
layout(location =3) in vec3 fragNormalWorld;
layout(location =4) in flat uint id;
layout(location =5) in vec4 clipspacepos;

struct PointLight {
    vec4 Position;
    vec4 Color;

    vec3 attenuation;// constant, linear quadratic stored in that order
};

struct DirectionalLight {
    vec3 direction;
    vec4 Color;
};

struct SpotLight {
    vec4 Position;
    vec3 direction;
    float cutoff;
    float outerCutoff;

    vec4 Color;
};

//global ubo
layout(set = 0, binding = 0) uniform GlobalUBO{
    mat4 proj; //camera
    mat4 view; //camera
    vec4 ambientlightcolor;// surrounding Color
    PointLight pointlights[50]; //
    DirectionalLight DirLight[10];
    SpotLight SptLight[10];
    int activepointlights;  
    int activeDirLights;
    int activeSpotLights;
}PL;

//data from the model
layout(push_constant) uniform Push {
    mat4 modelMatrix;
    mat4 normalMatrix;
    uint textureIndex;
    float padding[3]; 
    uint id;
} push;

void main(){
    if (abs(clipspacepos.x)>1.0|| abs(clipspacepos.y)>1.0 || abs(clipspacepos.z)>1.0) discard;
    int textureID = int(push.textureIndex);

    vec3 ambientlight = PL.ambientlight.xyz * PL.ambientlight.w;//intensity stored in w of vec4
    vec3 SurfaceNormal = normalize(fragNormalWorld);
    vec3 result = vec3(0.0,0.0,0.0);

    //sum of pointlight lighting;
    for (int i=0;i<PL.activepointlights; ++i){
        PointLight currentlight = PL.pointlights[i];
        vec3 directiontolight = PL.pointlights[i].Position.xyz - fragPosWorld;
        
        float atten = 1.0/(constant + (length(directiontolight)* linear) + (length(directiontolight)*quadratic));
        directiontolight = normalize(directiontolight);
        
        float cosAngleIncidence = max(dot(SurfaceNormal, directiontolight),0.0);
        vec3 intensity = currentlight.Color.xyz * currentlight.Color.w * 5 * atten;
        
        result += intensity * cosAngleIncidence;
    }

    for (int i=0; i<activeDirLights; ++i ){
        vec3 LightDirection = normalize(-Dirlight[i].direction);
        float diff = max(dot(fragNormalWorld, LightDirection), 0.0);

        vec3 diffuse = Dirlight[i].Color.rgb * diff;
        vec3 viewDirection = normalize(-fragPosWorld);
        vec3 
    }


}