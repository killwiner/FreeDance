#version 150 core

// Entrée
in vec2 translate;

// Uniform
uniform vec2 UNIF_win_resolution;
uniform vec2 UNIF_alpha_length;

// Sortie 
out vec4 outColor;

void main()
{
    vec2 uv = gl_FragCoord.xy / UNIF_win_resolution.xy;
    uv *= UNIF_alpha_length.y * 2.0f;
    uv = vec2(uv.x, uv.y) + vec2(-translate.x, -translate.y) * UNIF_alpha_length.y;
    uv = vec2(uv.x, 1.0 - uv.y);

    outColor = vec4(1.0, 1.0, 0.0 ,UNIF_alpha_length.x);
}
