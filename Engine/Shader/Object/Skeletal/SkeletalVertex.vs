#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexture;
layout(location = 3) in vec4 boneIds; 
layout(location = 4) in vec4 weights;

out vec3 Position;
out vec2 TexCoord;
out vec3 Normal;

out vec3 cameraPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

void main(void)
{
  vec4 totalPosition = vec4(0.0f, 0.0f, 0.0f, 1.0f);
  for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
  {
      if(boneIds[i] == -1) 
          continue;
      if(boneIds[i] >= MAX_BONES) 
      {
          totalPosition = vec4(vertexPosition, 1.0f);
          break;
      }
      vec4 localPosition = finalBonesMatrices[int(boneIds[i])] * vec4(vertexPosition, 1.0f);
      totalPosition += localPosition * weights[i];
      //vec3 localNormal = mat3(finalBoneMatrices[boneIds[i]]) * norm;
   }

  gl_Position = projection * view * model * totalPosition;

  Position =  vec3(model * vec4(vertexPosition, 1));
  Normal = vec3(model  * vec4(vertexNormal, 0));
  TexCoord = vertexTexture;

  cameraPosition = vec3(view[3][0], view[3][1], view[3][2]);
}