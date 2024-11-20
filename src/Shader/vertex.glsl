#version 330 core

layout(location=0)in vec2 mesh;
layout(location=1)in vec3 translate;
layout(location=2)in vec3 color;

out vec3 fragColor;

uniform mat4 viewProjection;

void main(){
  fragColor=color;

  float angle=radians(translate.z);
  mat2 rotation=mat2(cos(angle),-sin(angle),sin(angle),cos(angle));
  
  gl_Position=viewProjection*vec4(rotation*mesh+translate.xy,0.,1.);
}