#version 330

out vec4 color;
in vec4 vColor;
uniform vec3 triangleColor;

void main(){
	color = vColor;
}