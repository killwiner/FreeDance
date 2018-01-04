#version 150 core

// Entrée
in vec2 coordTexture;

// Uniform
uniform sampler2D texBackground;
//uniform sampler2D texMenu;

// Sortie 
out vec4 outColor;

void main()  
{
    vec4 colBackground = texture(texBackground, coordTexture) * vec4(1.0, 1.0, 1.0, 1.0);
//    vec4 colMenu = texture(texMenu, coordTexture) * vec4(1.0, 1.0, 1.0, 1.0);
//    outColor = mix(colBackground, colMenu, 0.5);
      outColor = colBackground;
}
