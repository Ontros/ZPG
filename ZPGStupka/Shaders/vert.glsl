#version 410
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn; 
layout(location = 0) out vec3 normal; 
out vec3 position;
uniform mat4 mat;
void main () {
     gl_Position = mat*vec4(vp, 1.0);
     position = vp;
     normal = vn;	
}
