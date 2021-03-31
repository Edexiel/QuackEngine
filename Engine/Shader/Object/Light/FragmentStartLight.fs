
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

//#define NB_MAX_DIRECTIONAL_LIGHT 16
uniform DirectionalLight directionalLights[NB_MAX_DIRECTIONAL_LIGHT];

//#define NB_MAX_POINT_LIGHT 16
uniform PointLight pointLights[NB_MAX_POINT_LIGHT];

//#define NB_MAX_SPOT_LIGHT 16
uniform SpotLight spotLights[NB_MAX_SPOT_LIGHT];

uniform uint nbDirectionalLights = 0;
uniform uint nbPointLights = 0;
uniform uint nbSpotLights = 0;