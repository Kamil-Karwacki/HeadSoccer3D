#version 450 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;

uniform sampler2D texture_diffuse1;

void main()
{    
    vec4 texColor = texture(texture_diffuse1, TexCoords);
    FragColor = texColor * vec4(ourColor, 1.0);
}

