#version 460

uniform mat4 u_ViewProjection;

layout (location = 0) in vec2 in_Position;
layout (location = 1) in vec4 in_Color;
layout (location = 2) in vec2 in_TextureCoordinates;
layout (location = 3) in float in_TextureIndex;
layout (location = 4) in float in_TilingFactor;

layout (location = 0) out vec4 out_Color;
layout (location = 1) out vec2 out_TextureCoordinates;
layout (location = 2) out flat float out_TextureIndex;
layout (location = 3) out flat float out_TilingFactor;

void main()
{
    out_Color = in_Color;
    out_TextureCoordinates = in_TextureCoordinates;
    out_TextureIndex = in_TextureIndex;
    out_TilingFactor = in_TilingFactor;

    gl_Position = u_ViewProjection * vec4(in_Position, 0, 1.0);
}
