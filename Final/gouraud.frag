#version 120

// Gouraud shading fragment shader

varying vec4 color;

void main()
{
    gl_FragColor = color;
}
