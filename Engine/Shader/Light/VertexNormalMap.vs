#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexture;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 biTangent;

out vec3 Position;
out vec2 TexCoord;
out vec3 Normal;

out vec3 cameraPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


out mat3 TBN;
  
void main(void)
{
  gl_Position = projection * view * model * vec4(vertexPosition,1);

  Position =  vec3(model * vec4(vertexPosition, 1));
  Normal = vec3(model  * vec4(vertexNormal, 0));
  TexCoord = vertexTexture;

  cameraPosition = vec3(view[3][0], view[3][1], view[3][2]);

  vec3 T = normalize(vec3(model * vec4(tangent,   0.0)));
  vec3 B = normalize(vec3(model * vec4(biTangent, 0.0)));
  vec3 N = normalize(vec3(model * vec4(vertexNormal, 0.0)));
  TBN = mat3(T, B, N);
}