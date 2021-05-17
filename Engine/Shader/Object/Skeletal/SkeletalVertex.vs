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

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

void main(void)
{
    mat4 BoneTransform = finalBonesMatrices[int(boneIds[0])] * weights[0];
    if (int(boneIds[1]) != -1)
        BoneTransform += finalBonesMatrices[int(boneIds[1])] * weights[1];
    if (int(boneIds[2]) != -1)
        BoneTransform += finalBonesMatrices[int(boneIds[2])] * weights[2];
    if (int(boneIds[3]) != -1)
        BoneTransform += finalBonesMatrices[int(boneIds[3])] * weights[3];


  gl_Position = projection * view * model * BoneTransform * vec4(vertexPosition, 1.0f);

  Position =  vec3(model * BoneTransform * vec4(vertexPosition, 1));
  Normal = vec3(model * BoneTransform * vec4(vertexNormal, 0));
  TexCoord = vertexTexture;

  cameraPosition = vec3(view[3][0], view[3][1], view[3][2]);
}