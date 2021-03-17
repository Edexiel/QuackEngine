#version 330 core

out vec4 FragColor;

in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;


struct material
{
  vec4 color;
sampler2D colorTexture;
};

vec4 GetColor(vec2 TexCoord)
{
    return texture(material.colorTexture, material.colorTexture) * material.color;
}
void main()
{
    FragColor = GetColor(TexCoord);
}