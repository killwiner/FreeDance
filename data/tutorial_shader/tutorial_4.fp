#version 150 core

// RGB COLOR MODEL AND COMPONENTS OF VECTORS
//
// After initialized, the components of vectors can be reached using
// the dot "." notation.
//
// A color is represented by three numbers (here in the range [0.0, 1.0])
// The model assumes the addition of pure red, green and blue lights
// of given intensities.

void main()  
{
    float redAmount = 0.6; // amount of redness
    float greenAmount = 0.2; // amount of greenness
    float blueAmount = 0.9; // amount of blueness
    
    vec3 color = vec3(0.0); 
    // Here we only input a single argument. It is a third way of
    // contructing vectors.
    // "vec3(x)" is equivalent to vec3(x, x, x);
    // This vector is initialized as
    // color.x = 0.0, color.y = 0.0; color.z = 0.0;
    color.x = redAmount;
    color.y = greenAmount;
    color.z = blueAmount;
    
    float alpha = 1.0;
    vec4 pixel = vec4(color, alpha);    
    gl_FragColor = pixel;
}
