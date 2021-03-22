vec3 GetMaterialSpecular(vec2 coordTexture)
{
    return material.specular * vec3(texture(material.specularTexture, coordTexture));
}