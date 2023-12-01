#version 330 core

out vec4 fragColor;

in vec3 fNormal;
in vec3 fPos;
in vec2 fTexture;

uniform sampler2D tex;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform int lightOn;


uniform vec3 fColor;

void main()
{
   

    if (fTexture.x>0) {
        fragColor = texture(tex, fTexture);
        return;
    }

   

    fragColor = vec4(fColor , 1.0);
}