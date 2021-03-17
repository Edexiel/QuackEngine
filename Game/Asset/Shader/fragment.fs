#version 330 core
out vec4 FragColor;
  
in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

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

#define NB_MAX_DIRECTIONAL_LIGHT 1
uniform DirectionalLight directionalLights[NB_MAX_DIRECTIONAL_LIGHT];

#define NB_MAX_POINT_LIGHT 2
uniform PointLight pointLights[NB_MAX_POINT_LIGHT];

#define NB_MAX_SPOT_LIGHT 2
uniform SpotLight spotLights[NB_MAX_SPOT_LIGHT];


uniform sampler2D ourTexture;

vec3 GetColorAfterDirectionalLight(DirectionalLight light, vec3 position, vec3 normal)
{
    
  //ambient
  vec3 ambient = light.ambient;

  //diffuse
  vec3 lightDir = normalize(-light.direction);
  float lightNor = max(dot(lightDir, normal), 0.0);
  vec3 diffuse = light.diffuse * lightNor;

  //specular Blinn - Phong

  vec3 viewDir    = normalize(cameraPosition - position);
  vec3 halfwayDir = normalize(lightDir + viewDir);

  float spec = pow(max(dot(normal, halfwayDir), 0.0), 128);//shininess);
  vec3 specular = light.specular * spec;

  vec3 reflected = ambient + diffuse + specular;
  
  return reflected;
}

vec3 GetColorAfterSpotLight(SpotLight light, vec3 position, vec3 normal)
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

  float spec = pow(max(dot(normal, halfwayDir), 0.0), 128);//shininess);
  vec3 specular = light.specular * spec;

  vec3 reflected = ambient + (diffuse + specular) * intensity;
  reflected *= attenuation;

  return reflected;

}

vec3 GetColorAfterPointLight(PointLight light, vec3 position, vec3 normal)
{
  float length = length(light.position - position);
  float attenuation = 1.0f / (light.constant + light.linear * length + 
    		    light.quadratic * (length * length));
  
    //ambient
  vec3 ambient = light.ambient;

    //diffuse
  vec3 lightDir = normalize(light.position - position);
  float lightNor = max(dot(lightDir, normal), 0.0);
  vec3 diffuse = light.diffuse * lightNor;

  //specular Blinn - Phong

  vec3 viewDir    = normalize(cameraPosition - position);
  vec3 halfwayDir = normalize(lightDir + viewDir);

  float spec = pow(max(dot(normal, halfwayDir), 0.0), 128);//shininess);
  vec3 specular = light.specular * spec;

  vec3 reflected = ambient + (diffuse + specular);
  reflected *= attenuation;

  return reflected;
}

void main()
{
    vec3 fragmentColor = vec3(0,0,0);

    fragmentColor += GetColorAfterPointLight(pointLights[0], vec3(Position), normalize(vec3(Normal)));
    //fragmentColor += GetColorAfterPointLight(pointLights[1], vec3(Position), normalize(vec3(Normal)));
    //fragmentColor += GetColorAfterPointLight(pointLights[2], vec3(Position), normalize(vec3(Normal)));
    //fragmentColor += GetColorAfterPointLight(pointLights[3], vec3(Position), normalize(vec3(Normal)));


    //fragmentColor += GetColorAfterDirectionalLight(directionalLights[0], vec3(Position), normalize(vec3(Normal)));

    //for (int i = 1 ; i < nbLights && i < NB_MAX_LIGHT ; i++)
    //{
    //  fragmentColor += GetColorAfterDirectionnalLight(lights[i], vec3(Position), normalize(vec3(Normal)));
    //}

    FragColor = texture(ourTexture, TexCoord) * vec4(fragmentColor, 1.f);
}