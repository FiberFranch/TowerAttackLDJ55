// -*- glsl -*-
#version 330

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec2 fragTexCoord;

// Input uniform values
uniform sampler2D texture0;
uniform int animationFrame;

// Output fragment color
out vec4 finalColor;

void main()
{
    vec4 texel = texture(texture0, fragTexCoord.x / 32.0 + 32 * animationFrame, fragTexCoord.y);
    texel.a = 1.0;
    finalColor = texel;
}
