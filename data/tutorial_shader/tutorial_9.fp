// VISUALISING THE COORDINATE SYSTEM
//
// Let's use a for loop and horizontal and vertical lines to draw
// a grid of the coordinate center

uniform ivec2 resolution;

void main()
{
    vec2 r = vec2( gl_FragCoord.xy / resolution.xy );
    
    vec3 backgroundColor = vec3(1.0);
    vec3 axesColor = vec3(0.0, 0.0, 1.0);
    vec3 gridColor = vec3(0.5);

    // start by setting the background color. If pixel's value
    // is not overwritten later, this color will be displayed.
    vec3 pixel = backgroundColor;
    
    // Draw the grid lines
    // we used "const" because loop variables can only be manipulated
    // by constant expressions.
    const float tickWidth = 0.1;
    for(float i=0.0; i<1.0; i+=tickWidth) {
        // "i" is the line coordinate.
        if(abs(r.x - i)<0.002) pixel = gridColor;
        if(abs(r.y - i)<0.002) pixel = gridColor;
    }
    // Draw the axes
    if( abs(r.x)<0.005 ) pixel = axesColor;
    if( abs(r.y)<0.006 ) pixel = axesColor;
    
    gl_FragColor = vec4(pixel, 1.0);
}
