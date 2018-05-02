#version 150 core

// Entrée
in vec2 coordTexture;
in vec2 translate;

// Uniform
uniform sampler2D UNIF_surface;
uniform vec2 UNIF_win_resolution;
uniform vec2 UNIF_tex_resolution;
uniform vec2 UNIF_alpha_length;
uniform float UNIF_time;

// Sortie 
out vec4 outColor;

const float speed = 0.8;
const float widthFactor = 4.0;

void main()
{
    // ration de proportionalité entre les dimension de la fenêtre et de la texture
    float ratio = (UNIF_tex_resolution.y * UNIF_win_resolution.x) / (UNIF_tex_resolution.x * UNIF_win_resolution.y);

    vec2 uv = gl_FragCoord.xy / UNIF_win_resolution.xy;
    uv *= UNIF_alpha_length.y * 2.0f;
    uv = vec2(uv.x  * ratio, uv.y) + vec2(-translate.x * ratio, -translate.y) * UNIF_alpha_length.y;
    uv = vec2(uv.x, 1.0 - uv.y);

// ------------ antialiasing -------------

    vec2 v = 2.0/UNIF_tex_resolution.xy;
    vec4 a = texture(UNIF_surface, uv);
    vec4 b = texture(UNIF_surface, uv + vec2(v.x, 0));

    b+= texture(UNIF_surface, uv-vec2(v.x, 0));
    b+= texture(UNIF_surface, uv+vec2(0, v.y));
    b+= texture(UNIF_surface, uv-vec2(0, v.y));
    
     b+= texture(UNIF_surface, uv+vec2(v.x, v.y));
     b+= texture(UNIF_surface, uv+vec2(v.x, -v.y));
    b+= texture(UNIF_surface, uv+vec2(-v.x, v.y));
    b+= texture(UNIF_surface, uv+vec2(-v.x, -v.y));
    b/=8.0;
    a += b;
    a/=1.4;

    vec4 colBackground = a * vec4(1.0f, 1.0f, 1.0f, UNIF_alpha_length.x);

    outColor = colBackground;
}
