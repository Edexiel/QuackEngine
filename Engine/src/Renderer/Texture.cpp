<<<<<<< HEAD
#include "../include/Renderer/Texture.hpp"

using namespace Renderer;

Texture::Texture(const unsigned int& _ID)
    : ID {_ID} {}
=======
#include <iostream>

#include "Renderer/Texture.hpp"
#include "glad/gl.h"


/*#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"*/

using namespace Renderer;

Texture::Texture(const unsigned int& ID): _ID{ID} {}

unsigned int Texture::GetID() const
{
  return _ID;
}
unsigned int Texture::LoadTexture(const char* filepath)
{
  /*
  GLuint IDTexture;

  glGenTextures(1, &IDTexture);
  glBindTexture(GL_TEXTURE_2D, IDTexture);

  // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // load and generate the texture

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(filepath, &width, &height, &nrChannels, 0);
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
    std::cout << "can't open image : " << filepath << std::endl;
  }

  stbi_image_free(data);*/

  return -1;
}
>>>>>>> d540025ad1119fcb334a5860e83b83ff476ceaa7
