#version 150 core

// "fragColor" is the output variable of the shader.
// Its value determines the image on the screen.
// This shaders sets its value to be the yellow color.

void main()  
{
    gl_FragColor = vec4(1.0, 1.0, 0.0 ,1.0);
}
