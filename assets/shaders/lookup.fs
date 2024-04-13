// -*- glsl -*-
#version 330

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;

// Input uniform values
uniform sampler2D texture0;
uniform sampler2D texture2;

// Output fragment color
out vec4 finalColor;

void main()
{
    // Selection
    vec4 texel = texture(texture2, fragTexCoord);
    texel.a = 1.0;
    finalColor = texel;
}
