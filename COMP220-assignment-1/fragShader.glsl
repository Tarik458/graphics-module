#version 330 core

out vec4 color;

in vec3 vertPosition;
in vec3 vertNorm;
in vec2 vertUV;

uniform sampler2D texSampler;
uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;
float shininess;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform Light light;

void main()
{
//// ambient
//vec3 ambient = light.ambient * texture(texture_diffuse, vertUV).rgb;

//basic
color = texture(texSampler, vertUV);


////diffuse
//vec3 norm = normalize(vertNorm);
//vec3 lightDir = normalize(light.position - vertPosition);
//float diff = max(dot(norm, lightDir), 0.0);
//vec3 diffuse = light.diffuse * diff * texture(texture_diffuse, TexCoords).rgb;  
//
//
////specular
//vec3 viewDir = normalize(viewPos - vertPosition);
//vec3 reflectDir = reflect(-lightDir, norm);  
//float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
//vec3 specular = light.specular * spec * texture(texture_specular, vertUV).rgb; 
//
//vec3 blend = ambient + diffuse + specular;
//
//color = vec4(blend, 1.0f);


}