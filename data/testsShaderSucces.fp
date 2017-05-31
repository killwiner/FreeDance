#version 150 core

// Entrée
in vec2 coordTexture;

// Uniform
uniform sampler2D tex;

// Sortie 
out vec4 outColor;

void main()  
{
    outColor = texture(tex, coordTexture) * vec4(.0, 1.0, .0, 1.0);
}
