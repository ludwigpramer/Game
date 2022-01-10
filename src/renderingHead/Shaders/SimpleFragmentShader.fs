#version 330 core

//input data
in vec2 UV;

//Output data
out vec3 color;

//values that stay constant for the whole mesh
uniform sampler2D myTextureSampler;


void main(){
  color = texture(myTextureSampler, UV).rgb;
}