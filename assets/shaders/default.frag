#version 450 core
out vec4 FragColor;

in vec2 v_texCoords;
in vec3 v_color;
in vec3 v_fragPos;
in vec3 v_normal;

struct DirLight 
{
    vec3 direction;
    vec3 color;
    float ambient;
    float diffuse;
    float specular;
};

uniform sampler2D u_textureDiffuse1;
uniform DirLight u_dirLight;
uniform vec3 u_viewPos;

vec3 calculateDirLight();

void main()
{    
    vec3 directionalLight = calculateDirLight();
    FragColor = vec4(directionalLight, 1.0);
}

vec3 calculateDirLight()
{
    vec3 normal = normalize(v_normal);
    vec3 lightDir = normalize(u_dirLight.direction);
    vec3 viewDir = normalize(u_viewPos - v_fragPos);

    vec3 objectColor = (texture(u_textureDiffuse1, v_texCoords) * vec4(v_color, 1.0)).rgb;

    // ambient
    vec3 ambient = u_dirLight.ambient * u_dirLight.color;

    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = u_dirLight.diffuse * diff * u_dirLight.color;

    // specular
    vec3 halfwayDir = normalize(lightDir + viewDir);
    // 32 = shininess
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 2.0);
    vec3 specular = u_dirLight.specular * spec * u_dirLight.color;

    vec3 finalLight = ambient + diffuse + specular;
    return finalLight * objectColor;
}

