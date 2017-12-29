#version 150 core

// MOVING THE COORDINATE CENTER TO THE CENTER OF THE FRAME
//
// Instead of mapping [0, iResolution.x]x[0, iResolution.y] region to
// [0,1]x[0,1], lets map it to [-1,1]x[-1,1]. This way the coordinate
// (0,0) will not be at the lower left corner of the screen, but in the
// middle of the screen.

uniform ivec2 resolution;

void main()
{
    vec2 r = vec2( gl_FragCoord.xy - 0.5 * resolution.xy );
    // [0, resolution.x] -> [-0.5 * resolution.x, 0.5 * resolution.x]
    // [0, resolution.y] -> [-0.5 * resolution.y, 0.5 * resolution.y]
    r = 2.0 * r.xy / resolution.xy;
    // [-0.5 * resolution.x, 0.5 * resolution.x] -> [-1.0, 1.0]
    
    vec3 backgroundColor = vec3(1.0);
    vec3 axesColor = vec3(0.0, 0.0, 1.0);
    vec3 gridColor = vec3(0.5);

    // start by setting the background color. If pixel's value
    // is not overwritten later, this color will be displayed.
    vec3 pixel = backgroundColor;
    
    // Draw the grid lines
    // This time instead of going over a loop for every pixel
    // we'll use mod operation to achieve the same result
    // with a single calculation.
    const float tickWidth = 0.1;
    if( mod(r.x, tickWidth) < 0.008 )
        pixel = gridColor;
    if( mod(r.y, tickWidth) < 0.008 )
        pixel = gridColor;
    // Draw the axes
    if( abs(r.x)<0.006 )
        pixel = axesColor;
    if( abs(r.y)<0.007 )
        pixel = axesColor;
    
    gl_FragColor = vec4(pixel, 1.0);
}


