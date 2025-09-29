#version 410
layout(location=0) in vec3 normal;
in vec3 position;
out vec4 frag_colour;
void main () {
     frag_colour = vec4(normal, 1.0f);
};
