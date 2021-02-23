#include "Renderer/Texture.hpp"
#include "glad/gl.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Renderer;

Texture::Texture(const unsigned int& ID): _ID{ID} {}

Texture::Texture(const char *filename, bool antiAliasing)
{
  _ID = LoadTexture(filename, antiAliasing);
  loaded = true;
  _name = filename;
}

unsigned int Texture::LoadTexture(const char *filename, bool antiAliasing) //, int width, int height)
{
  glEnable(GL_TEXTURE_2D);

  GLuint nbTexture;

  glGenTextures(1, &nbTexture);
  glBindTexture(GL_TEXTURE_2D, nbTexture);

  // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  if (antiAliasing)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }
  else
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }

  // load and generate the texture

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
  if (data)
  {
    if (nrChannels == 4)
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "can't open image : " << filename << std::endl;
  }

  stbi_image_free(data);

  glDisable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, nbTexture);
  glFlush();

  return nbTexture;
}
void Texture::FreeTexture(unsigned int &texture)
{
  glDeleteTextures(1, &texture);
}
Texture::~Texture()
{
  FreeTexture(_ID);
}
