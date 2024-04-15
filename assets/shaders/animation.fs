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
    vec2 coord = vec2(fragTexCoord.x/8.0 + animationFrame/8.0, fragTexCoord.y);
    vec4 texel = texture(texture0, coord);
    finalColor = texel;
}
