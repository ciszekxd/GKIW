#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


uniform vec4 color=vec4(1,1,1,1);
uniform vec4 lightDir=vec4(0,0,1,0);

//Atrybuty
//layout (location=0) in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
//layout (location=1) in vec4 normal; //wektor normalny w wierzcholku

//kfowe rzeczy
layout (location=0) in vec4 KF1;
layout (location=1) in vec4 KF2;
layout (location=2) in vec4 KF1norms;
layout (location=3) in vec4 KF2norms;
uniform float time;

//

//Zmienne interpolowane
out vec4 i_color;

void main(void) {
    vec4 tempVertices = mix(KF1, KF2, time);
    vec4 tempNormals = mix(KF1norms, KF2norms, time);

    gl_Position=P*V*M*tempVertices;

    mat4 G=mat4(inverse(transpose(mat3(M))));
    vec4 n=normalize(V*G*tempNormals);

    float nl=clamp(dot(n,lightDir),0,1);

    i_color=vec4(color.rgb*nl,color.a);
}