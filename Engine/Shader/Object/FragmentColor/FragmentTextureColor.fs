vec4 GetColor(Material material, vec2 TexCoord)
{
    return texture(material.colorTexture, TexCoord) * material.color;
}