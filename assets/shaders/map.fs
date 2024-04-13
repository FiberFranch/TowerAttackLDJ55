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
uniform vec4 colDiffuse;
uniform int selectedTile;
uniform int isPlacable;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

#define     LIGHT_DIRECTIONAL       0
#define     LIGHT_POINT             1

struct Light {
    int enabled;
    int type;
    vec3 position;
    vec3 target;
    vec4 color;
};

// Input lighting values
vec4 ambient = vec4(0.2);
uniform vec3 viewPos;

uint bytesToUint(vec4 bytes) {
    // Combine the bytes into a single 32-bit integer
    // uint rgba = uint(bytes.r*255.0) << 24 | uint(bytes.g*255.0) << 16 | uint(bytes.b*255.0) << 8 | uint(bytes.a*255.0);
    // return rgba;
    float red = float(bytes.r) * 255.0;
    float green = float(bytes.g) * 255.0 * 256.0;
    float blue = float(bytes.b) * 255.0 * 256.0 * 256.0;
    uint index = uint(red) + uint(green) + uint(blue);
    return index;
}

void main()
{
    vec3 lightDot = vec3(0.0);
    vec3 normal = normalize(fragNormal);
    vec3 viewD = normalize(viewPos - fragPosition);
    vec3 specular = vec3(0.0);

    Light light;

    light.enabled = 1;
    light.type = LIGHT_DIRECTIONAL;
    light.position = vec3(0, 8, 4);
    light.target = vec3(0, 0, 0);
    light.color = vec4(0.9); // white light

    if (light.enabled == 1){
      vec3 light_vec = vec3(0.0);

      if (light.type == LIGHT_DIRECTIONAL)
      {
        light_vec = normalize(light.position - light.target);
      }

      if (light.type == LIGHT_POINT)
      {
        light_vec = normalize(light.position - fragPosition);
      }

      float NdotL = max(dot(normal, light_vec), 0.0);
      lightDot += light.color.rgb * NdotL;

      float specCo = 0.0;
      if (NdotL > 0.0) specCo = pow(max(0.0, dot(viewD, reflect(-(light_vec), normal))), 16.0); // 16 refers to shine
      specular += specCo;
    }

    vec4 textureColor = texture(texture0, fragTexCoord);
    finalColor = (textureColor)*vec4(lightDot, 1.0);
    finalColor += (ambient)*colDiffuse;

    // Selection
    vec4 textureIndex = texture(texture2, fragTexCoord);
    int index = int(bytesToUint(textureIndex));
    vec4 selection = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 highlight = vec4(1.0, 1.3, 1.5, 1.0);
    if (isPlacable == 0) {
        highlight = vec4(1.8, 0.9, 0.9, 1.0);
    }
    if (index == selectedTile) {
        selection *= highlight;
    }
    finalColor *= selection;
}
