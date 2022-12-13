#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Textures[2];

void main()
{
    // color = v_Color;
    // color = vec4(v_TexCoord, 0.0, 1.0);
    int index = int(v_TexIndex);

    color = texture(u_Textures[index], v_TexCoord);
}