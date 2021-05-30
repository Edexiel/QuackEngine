
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexture;

#ifdef SKELETON
    layout(location = 3) in ivec4 boneIds;
    layout(location = 4) in vec4 weights;

    const int MAX_BONES = 100;
    const int MAX_BONE_INFLUENCE = 4;
    uniform mat4 finalBonesMatrices[MAX_BONES];
#endif

#ifdef NORMAL
    layout(location = 3) in vec3 tangent;
    layout(location = 4) in vec3 biTangent;

    out mat3 TBN;
#endif

out vec3 Position;
out vec2 TexCoord;
out vec3 Normal;

out vec3 cameraPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main(void)
{
    mat4 BoneTransform = {1.0f};
    #ifdef SKELETON

        mat4 BoneTransform = finalBonesMatrices[int(boneIds[0])] * weights[0];
        if (int(boneIds[1]) != -1)
            BoneTransform += finalBonesMatrices[int(boneIds[1])] * weights[1];
        if (int(boneIds[2]) != -1)
            BoneTransform += finalBonesMatrices[int(boneIds[2])] * weights[2];
        if (int(boneIds[3]) != -1)
            BoneTransform += finalBonesMatrices[int(boneIds[3])] * weights[3];


    #endif

    gl_Position = projection * view * model * BoneTransform * vec4(vertexPosition, 1.0f);

        //gl_Position = projection * view * model * vec4(vertexPosition,1);


    Position =  vec3(model * vec4(vertexPosition, 1));
    Normal = vec3(model  * vec4(vertexNormal, 0));
    TexCoord = vertexTexture;

    cameraPosition = vec3(view[3][0], view[3][1], view[3][2]);

    #ifndef NORMAL
        vec3 T = normalize(vec3(model * vec4(tangent,   0.0)));
        vec3 B = normalize(vec3(model * vec4(biTangent, 0.0)));
        vec3 N = normalize(vec3(model * vec4(vertexNormal, 0.0)));
        TBN = mat3(T, B, N);
    #endif
}