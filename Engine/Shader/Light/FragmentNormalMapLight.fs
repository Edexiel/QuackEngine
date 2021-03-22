
in mat3 TBN;

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
