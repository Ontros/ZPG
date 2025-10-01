#version 410
in vec3 position;
out vec4 frag_colour;
void main () {
    frag_colour = vec4 (position.r, position.g, position.b + 0.5, 1.0);
}