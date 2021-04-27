#version 330 core

out vec4 color;

in vec3 vertNorm;
in vec2 vertUV;

uniform sampler2D texSampler;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;


uniform LightBlock {

vec3 lightDir;
vec3 lightColour;
};

uniform vec3 objColour;


void main()
{
 // color = vertColour;

 color = texture(texSampler, vertUV);

// color = vec4(0.5f, 0.5f, 0.0f, 1);

//color = vec4(vertNorm, 1.0f);

//vec3 lightDir = vec3(0.0f, 1.0f, 0.0f);
//vec3 lightColour = vec3(1.0f, 1.0f, 1.0f);
//vec3 objColour = vec3(1.0f, 0.0f, 0.0f);



vec3 norm = normalize(vertNorm);
vec3 lightNorm = normalize(lightDir);

vec3 baseColour = objColour.x < 0.0f ? texture(texSampler, vertUV).xyz :  objColour;

float diffuseFactor = max(dot(norm, lightNorm), 0.0f);
vec3 diffuse = diffuseFactor * lightColour;
//color = vec4(diffuse * baseColour, 1.0f);


}