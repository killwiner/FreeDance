#version 150 core

// RESOLUTION, THE FRAME SIZE
//
// If you resize your browser, or go to fullscreen mode and come back
// you'll see that the ratio of the width of the first color to the
// second color changes with screen size.
// It is because we set the width of the strip in absolute number of
// pixels, rather than as a proportion of the screen width and height.
//
// Say we want to paint the left and right halves with different colors.
// Without knowing the number of pixels horizontally, we cannot prepare
// a shader that works on all frame sizes.
// 
// How can we learn the screen size (the width and height) in terms of 
// the number of pixel. It is given us in the variable "iResolution".
// "iResolution.x" is the width of the frame, and
// "iResolution.y" is the height of the frame

uniform ivec2 resolution;

void main()  
{
    vec3 color1 = vec3(0.741, 0.635, 0.471);
    vec3 color2 = vec3(0.192, 0.329, 0.439);
    vec3 pixel;
    
    pixel = ( gl_FragCoord.x > resolution.x / 2.0 ) ? color2 : color1;
    
    gl_FragColor = vec4(pixel, 1.0);
}
