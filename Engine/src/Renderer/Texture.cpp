#include <iostream>
#include "Renderer/Texture.hpp"
#include "Renderer/RendererPlatform.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Renderer;

Texture::Texture() : Asset(Resources::ASSET_TYPE::A_TEXTURE){}

Texture::Texture(unsigned int ID): Asset(Resources::ASSET_TYPE::A_TEXTURE), ID{ID} {}

unsigned int Texture::GetID() const
{
  return ID;
}

Texture Texture::LoadTexture(const std::filesystem::path& path)
{
  Texture texture(RendererPlatform::CreateTexture());
  RendererPlatform::TextureParameter();

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
  if (data)
  {
    RendererPlatform::SetTextureImage2D(data, nrChannels, width, height);
  }
  else
  {
    std::cout << "[Texture] Can't open image : " << path.string() << std::endl;
  }
  stbi_image_free(data);

  return texture;
}

void Texture::Bind(unsigned int index) const
{
  RendererPlatform::BindTexture(ID, index);
}