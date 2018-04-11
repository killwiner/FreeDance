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
uniform int UNIF_idShader;

// Sortie 
out vec4 outColor;

const float speed = 0.8;
const float widthFactor = 4.0;

vec2 saturate(vec2 v) {
    return clamp(v, 0.0, 1.0);
}

vec3 calcSine(vec2 uv, 
              float frequency, float amplitude, float shift, float offset,
              vec3 color, float width, float exponent)
{
    float angle = UNIF_time * speed * frequency + (shift + uv.x) * 6.2831852;
    float y = sin(angle) * amplitude + offset;
    float scale = pow(smoothstep(width * widthFactor, 0.0, distance(y, uv.y)), exponent);
    return color * scale;
}

void main()
{
    // ration de proportionalité entre les dimension de la fenêtre et de la texture
    float ratio = (UNIF_tex_resolution.y * UNIF_win_resolution.x) / (UNIF_tex_resolution.x * UNIF_win_resolution.y);

    vec2 uv = gl_FragCoord.xy / UNIF_win_resolution.xy;
    uv *= UNIF_alpha_length.y * 2.0f;
    uv = vec2(uv.x  * ratio, uv.y) + vec2(-translate.x * ratio, -translate.y) * UNIF_alpha_length.y;

    if(UNIF_idShader == 0) {
      uv = uv + vec2(sin(uv.y * 7.0 + UNIF_time * .01) * 0.02, 
                   cos(uv.x * 5.0 + UNIF_time * .08) * 0.02) * .4; 
    }

    uv = vec2(uv.x, 1.0 - uv.y);

// antialiasing
    //uv *= UNIF_tex_resolution;
    //vec2 val = (saturate(fract(uv) / saturate(fwidth(uv))) + floor(uv) - 1.0) / UNIF_tex_resolution;
    //val = vec2(val.x, 1.0 - val.y);

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

    //vec4 colBackground = texture(UNIF_surface, uv) * vec4(1.0f, 1.0f, 1.0f, UNIF_alpha_length.x);
    vec4 colBackground = a * vec4(1.0f, 1.0f, 1.0f, UNIF_alpha_length.x);

    if(UNIF_idShader != 0) {
        outColor = colBackground;
        return;
    }


// ---------------------------- //

    uv = (gl_FragCoord.xy / UNIF_win_resolution.xy);
//    uv -= vec2(0.5);
    uv.x *= UNIF_win_resolution.x/UNIF_win_resolution.y;
  
    float m = sin(UNIF_time / 2.0);
    float n = sin(UNIF_time / 4.0);
    float l = cos(UNIF_time / 4.0);
 
    vec3 color = vec3(0.0);
//    color += calcSine(uv, 0.20, 0.05, 0.0, 0.5, vec3(0.0, 0.0, 1.0), 0.2, 25.0);
    color += calcSine(uv, 0.2, l * 0.05, UNIF_time / 24.0, .5 + .05 * m, vec3(n, 0.8, 1.0), .05 + abs(.05 * m), 25.0); 
    color += calcSine(uv, 0.2, n * 0.05, UNIF_time / 32.0, .5 - .05 * m, vec3(l, 0.8, 1.0), .05 + abs(.05 * l), 25.0);
    color += calcSine(uv, 0.18, 0.07, 0.0, 0.5, vec3(0.0, 0.0, 0.7), 0.2, 15.0);
    color += calcSine(uv, 0.46, 0.07, 0.0, 0.5, vec3(0.2, m, 0.7), 0.05, 23.0);
    color += calcSine(uv, 0.58, 0.05, 0.0, 0.3, vec3(0.0, 0.0, 0.7), 0.2, 15.0);

    
    // Calculate the final color mixing lines and backgrounds
//    vec3 bg = mix( vec3(0.93, 0.71, 0.62), vec3(0.9, 0.44, 0.44), r);
//    bg = mix(bg, vec3(0.9, 0.91, 0.62), c);
//    bg = mix(bg, vec3(0.9, 0.91, 0.82), s);
//      vec4 bg = mix(colBackground, vec4(0.3, 0.41, 0.92, 1.0), c);

      vec3 bg = mix(vec3(colBackground), color, .3);
    
      outColor = vec4(bg, 1.0);

}
