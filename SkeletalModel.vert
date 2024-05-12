#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec3 color;
layout(location = 3) in vec2 tex;
layout(location = 4) in ivec4 boneIds; 
layout(location = 5) in vec4 weights;
	
// Imports the camera matrix from the main function
uniform mat4 projection;
uniform mat4 view;

uniform mat4 model;
	
const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];
	
// Outputs the current position for the Fragment Shader
out vec3 crntPos;
// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the color for the Fragment Shader
out vec3 fragColor;
// Outputs the texture coordinates to the Fragment Shader
out vec2 texCoord;


flat out ivec4 fragBoneIds;
out vec4 fragWeights;
	
void main()
{
    vec4 totalPosition = vec4(0.0f);
    for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
    {
        if(boneIds[i] == -1) 
            continue;
        if(boneIds[i] >=MAX_BONES) 
        {
            totalPosition = vec4(pos,1.0f);
            break;
        }
        vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(pos,1.0f);
        totalPosition += localPosition * weights[i];
        vec3 localNormal = mat3(finalBonesMatrices[boneIds[i]]) * norm;
    }
		
    crntPos = vec3(model * totalPosition);
	Normal = mat3(transpose(inverse(model))) * norm;
	fragColor = color;
	texCoord = tex;
    fragBoneIds = boneIds;
    fragWeights = weights;

    gl_Position =  projection * view * model * totalPosition;
    //gl_Position =  projection * view * vec3(model * vec4(aPos, 1.0f));
    //gl_Position = camMatrix * vec4(crntPos, 1.0);
}