#include <iostream>
#include "Renderer/Texture.hpp"
#include "Renderer/RendererPlatform.hpp"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Renderer;

Texture::Texture(const unsigned int& ID): _ID{ID} {}
Texture::~Texture()
{
  RendererPlatform::DeleteTexture(_ID);
}

unsigned int Texture::GetID() const
{
  return _ID;
}
unsigned int Texture::LoadTexture(const char* filepath)
{
  unsigned int IDTexture = RendererPlatform::CreateTexture();

  RendererPlatform::TextureParameter();

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(filepath, &width, &height, &nrChannels, 0);
  if (data)
  {
    RendererPlatform::SetTextureImage2D(data, nrChannels, width, height);
  }
  else
  {
    std::cout << "can't open image : " << filepath << std::endl;
  }
  stbi_image_free(data);

  return IDTexture;
}
void Texture::Bind()
{
  RendererPlatform::BindTexture(_ID);
}
