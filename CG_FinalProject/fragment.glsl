#version 330 core

in vec2 fTexture;

out vec4 fragColor;

uniform sampler2D tex;
uniform vec3 fColor;

void main()
{
    if (fTexture.x>0) {
        fragColor = texture(tex, fTexture);
        return;
    }

    fragColor = vec4(fColor , 1.0);
}