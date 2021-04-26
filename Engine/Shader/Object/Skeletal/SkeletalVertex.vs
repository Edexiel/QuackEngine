#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexture;
layout(location = 3) in ivec4 boneIds; 
layout(location = 4) in vec4 weights;

out vec3 Position;
out vec2 TexCoord;
out vec3 Normal;

out vec3 cameraPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

  
void main(void)
{
  gl_Position = projection * view * model * vec4(vertexPosition,1);

  Position =  vec3(model * vec4(vertexPosition, 1));
  Normal = vec3(model  * vec4(vertexNormal, 0));
  TexCoord = vertexTexture;

  cameraPosition = vec3(view[3][0], view[3][1], view[3][2]);
}