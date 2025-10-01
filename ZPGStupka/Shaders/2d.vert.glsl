#version 410
layout(location=0) in vec3 vp;
out vec3 position;
void main () {
    gl_Position = vec4 (vp.x, vp.y, vp.z, 1.0);
    position = vp;
}