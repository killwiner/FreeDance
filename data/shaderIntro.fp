#version 150 core

// Entrée
in vec2 coordTexture;
in vec2 translate;

// Uniform
uniform sampler2D UNIF_surface;
uniform vec2 UNIF_win_resolution;
uniform vec2 UNIF_tex_resolution;
uniform vec2 UNIF_alpha_length;

// Sortie 
out vec4 outColor;

vec2 saturate(vec2 v) {
    return clamp(v, 0.0, 1.0);
}

void main()
{
    // ration de proportionalité entre les dimension de la fenêtre et de la texture
    float ratio = (UNIF_tex_resolution.y * UNIF_win_resolution.x) / (UNIF_tex_resolution.x * UNIF_win_resolution.y);

    vec2 uv = gl_FragCoord.xy / UNIF_win_resolution.xy;
    uv *= UNIF_alpha_length.y * 2.0f;
    uv = vec2(uv.x  * ratio, uv.y) + vec2(-translate.x * ratio, -translate.y) * UNIF_alpha_length.y;

// antialiasing
    uv *= UNIF_tex_resolution;
    vec2 val = (saturate(fract(uv) / saturate(fwidth(uv))) + floor(uv) - 1.0) / UNIF_tex_resolution;
    val = vec2(val.x, 1.0 - val.y);

    vec4 colBackground = texture(UNIF_surface, val) * vec4(1.0f, 1.0f, 1.0f, UNIF_alpha_length.x);
    outColor = colBackground;

// ---------------------------- //

//    float iTime = .0f;

//    vec2 uv = (gl_FragCoord.xy / win_resolution.xy);
//    uv -= vec2(0.5);
//    uv.x *= win_resolution.x/win_resolution.y;
    
    // Calculate polar coordinates
//    float r = length(uv);
//    float a = atan(uv.y, uv.x);
       
    // Draw the lines
//    const float it = 5.0;
//    float c = 0.0;
//    for( float i = 0.0 ; i < it ; i += 1.0 )
//    {
//        float i01 = i / it;
//        float rnd = texture( texBackground, vec2(i01)).x;
//        float react = texture( texBackground, vec2(i01, 0.0) ).x;    
        
//        float c1 = (uv.x + 1.1 + react) * 0.004 * abs( 1.0 / sin( (uv.y +0.25) +
//                                                         sin(uv.x * 4.0 * rnd + rnd * 7.0 + iTime * 0.75) *
//                                                                 (0.01 + 0.15*react)) );
//        c = clamp(c + c1, 0.0, 1.0);
//    }
    
//    float s = 0.0;
//    const float it2 = 20.0;
//    for( float i = 0.0 ; i < it2 ; i += 1.0 )
//    {
//        float i01 = i / it2;       
//        float react = texture( texBackground, vec2(i01, 0.0) ).x;  
//        vec2 rnd = texture( texBackground, vec2(i01)).xy;
//        vec2 rnd2 = rnd - 0.5;
      
//        rnd2 = vec2(0.85*sin(rnd2.x * 200.0 + rnd2.y * iTime * 0.1), 
//                    -0.1 - 0.15 * sin(rnd2.x * rnd2.x * 200.0 + iTime  * rnd2.x * 0.25));
        
//        float r1 = 1.0 - length(uv - rnd2);
//        float rad = ( 1.0 - clamp(0.03 * rnd.y + react * 0.05, 0.0, 1.0) );

//        r1 = smoothstep(rad, rad + 0.015, r1);
//        s += r1;
//    }
    
    // Calculate the final color mixing lines and backgrounds
//    vec3 bg = mix( vec3(0.93, 0.71, 0.62), vec3(0.9, 0.44, 0.44), r);
//    bg = mix(bg, vec3(0.9, 0.91, 0.62), c);
//    bg = mix(bg, vec3(0.9, 0.91, 0.82), s);
    
//    outColor = vec4(bg, 1.0);

}
