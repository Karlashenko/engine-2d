#version 460

uniform sampler2D u_Textures[32];

layout (location = 0) in vec4 in_Color;
layout (location = 1) in vec2 in_TextureCoordinates;
layout (location = 2) in flat float in_TextureIndex;
layout (location = 3) in flat float in_TilingFactor;

layout (location = 0) out vec4 out_Color;

void main()
{
    out_Color = texture(u_Textures[int(in_TextureIndex)], in_TextureCoordinates * in_TilingFactor) * in_Color;
}
