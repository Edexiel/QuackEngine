vec3 GetMaterialAmbient(vec2 coordTexture)
{
    return material.ambient * vec3(texture(material.diffuseTexture, coordTexture));
}

vec3 GetMaterialDiffuse(vec2 coordTexture)
{
    return material.diffuse * vec3(texture(material.diffuseTexture, coordTexture));
}