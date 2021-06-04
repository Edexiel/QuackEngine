out vec4 FragColor;

in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

struct Material
{
    vec4 color;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;

    sampler2D colorTexture;
    sampler2D diffuseTexture;
    sampler2D specularTexture;
    sampler2D normalMap;
};

#ifdef LIGHT

in vec3 cameraPosition;

struct DirectionalLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float spotAngle;
    float outerSpotAngle;
};

//#define NB_MAX_DIRECTIONAL_LIGHT 16
uniform DirectionalLight directionalLights[NB_MAX_DIRECTIONAL_LIGHT];

//#define NB_MAX_POINT_LIGHT 16
uniform PointLight pointLights[NB_MAX_POINT_LIGHT];

//#define NB_MAX_SPOT_LIGHT 16
uniform SpotLight spotLights[NB_MAX_SPOT_LIGHT];

uniform uint nbDirectionalLights = 0u;
uniform uint nbPointLights = 0u;
uniform uint nbSpotLights = 0u;
#endif

uniform Material material;

#ifdef NORMALMAP
in mat3 TBN;
#endif

#ifdef TEXTURECOLOR
    vec4 GetColor(Material material, vec2 TexCoord)
    {
        return texture(material.colorTexture, TexCoord) * material.color;
    }
#else
    vec4 GetColor(Material material, vec2 TexCoord)
    {
        return material.color;
    }
#endif

#ifdef TEXTUREDIFFUSE
    vec3 GetMaterialAmbient(vec2 coordTexture)
    {
        return material.ambient * vec3(texture(material.diffuseTexture, coordTexture));
    }

    vec3 GetMaterialDiffuse(vec2 coordTexture)
    {
        return material.diffuse * vec3(texture(material.diffuseTexture, coordTexture));
    }
#else
    vec3 GetMaterialAmbient(vec2 coordTexture)
    {
        return material.ambient;
    }

    vec3 GetMaterialDiffuse(vec2 coordTexture)
    {
        return material.diffuse;
    }
#endif

#ifdef TEXTURESPECULAR
    vec3 GetMaterialSpecular(vec2 coordTexture)
    {
        return material.specular * vec3(texture(material.specularTexture, coordTexture));
    }
#else
    vec3 GetMaterialSpecular(vec2 coordTexture)
    {
        return material.specular;
    }
#endif

#ifdef LIGHT

vec3 GetColorAfterDirectionalLight(DirectionalLight light, vec3 position, vec3 normal, vec2 texCoord)
{

    //diffuse
    vec3 lightDir = normalize(-light.direction);
    float lightNor = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = light.diffuse * max(dot(lightDir, normal), 0.0);

    //specular Blinn - Phong

    vec3 viewDir    = normalize(cameraPosition - position);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec;

    return light.ambient * GetMaterialAmbient(texCoord) + diffuse * GetMaterialDiffuse(texCoord) + specular * GetMaterialSpecular(texCoord);
}

vec3 GetColorAfterPointLight(PointLight light, vec3 position, vec3 normal, vec2 texCoord)
{
    float length = length(light.position - position);
    float attenuation = 1.0f / (light.constant + light.linear * length +
    light.quadratic * (length * length));

    //diffuse
    vec3 lightDir = normalize(light.position - position);
    vec3 diffuse = light.diffuse * max(dot(lightDir, normal), 0.0);

    //specular Blinn - Phong
    vec3 specular = light.specular * pow(max(dot(normal, normalize(lightDir + normalize(cameraPosition - position))), 0.0), material.shininess);

    return (light.ambient * GetMaterialAmbient(texCoord) + diffuse * GetMaterialDiffuse(texCoord) + specular * GetMaterialSpecular(texCoord)) * attenuation;
}

vec3 GetColorAfterSpotLight(SpotLight light, vec3 position, vec3 normal, vec2 texCoord)
{
    float length = length(light.position - position);
    float attenuation = 1.0f / (light.constant + light.linear * length +
    light.quadratic * (length * length));

    float theta     = degrees(acos(dot(normalize((light.position - position)), normalize(-light.direction))));
    float epsilon   = light.spotAngle - light.outerSpotAngle;
    float intensity = clamp((theta - light.outerSpotAngle) / epsilon, 0.0, 1.0);

    //ambient
    vec3 ambient = light.ambient;

    //diffuse
    vec3 lightDir = normalize(-light.direction);
    float lightNor = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = light.diffuse * lightNor;

    //specular Blinn - Phong

    vec3 viewDir    = normalize(cameraPosition - position);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec;

    //vec3 reflected = ambient + (diffuse + specular) * intensity;
    //reflected *= attenuation;

    return ((light.ambient * GetMaterialAmbient(texCoord) +
    diffuse * GetMaterialDiffuse(texCoord) +
    specular * GetMaterialSpecular(texCoord))
    * intensity) * attenuation;

}

#endif

void main()
{
    vec3 normal = normalize(Normal);

    #ifdef NORMALMAP
        normal = texture(material.normalMap, TexCoord).rgb;
        normal = normalize(TBN * (normal * 2.0 - 1.0));
    #endif

    #ifdef LIGHT
        vec3 fragmentColor = vec3(0,0,0);
        for (uint i = 0u ; i < nbDirectionalLights ; i++)
            fragmentColor += GetColorAfterDirectionalLight(directionalLights[i], vec3(Position), normal, TexCoord);
        for (uint i = 0u ; i < nbPointLights ; i++)
            fragmentColor += GetColorAfterPointLight(pointLights[i], vec3(Position), normal, TexCoord);
        for (uint i = 0u ; i < nbSpotLights ; i++)
            fragmentColor += GetColorAfterSpotLight(spotLights[i], vec3(Position), normal, TexCoord);

        FragColor = GetColor(material, TexCoord) * vec4(fragmentColor, 1.f);
    #else
        FragColor = GetColor(material, TexCoord);
    #endif


}