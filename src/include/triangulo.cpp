#include "forms.hpp"
#include <iostream>
#include <cmath>


void triangulo::geraVertices(float* v){
    for(int i=0; i<6; i++){ vertices[i] = v[i]; }
}

//depois de inicializado o opengl
void triangulo::setVAO(){
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
}
void triangulo::setVBO(){
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}
void triangulo::configVerxtexs(){
    //envia os dados para o buffer
    //STATIC para quando os dados não mudam
    //DYNAMIC para quando eles forem animados
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //diz ao openGL como vai ler os dados
    // atributo location = 0, 2 floats por vértice (x,y)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    //ativa o atributo 0, que o vertex shader vai usar como entrada
    glEnableVertexAttribArray(0);
}

//auxiliares para shader program -------
const char* triangulo::geraShader(){
    return R"(
#version 330 core
//uniform float u_time;
layout(location = 0) in vec2 vitor;
void main() {
    //float offset = cos(u_time*10)*0.5;
    //vec2 pos = vec2(offset, offset);
    gl_Position = vec4(vitor, 0, 1.0);
}
)";

}
void triangulo::setVertexShader(){
    const char* shader = geraShader();
    //cria o objeto
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //insere código GLSL
    glShaderSource(vertexShader, 1, &shader, NULL);
    //compila na GPU
    glCompileShader(vertexShader);

    //boas práticas
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Erro no Vertex Shader:\n" << infoLog << std::endl;
    }
}
//codigo para mudar a cor do objeto que vai ser mostrado
const char* triangulo::geraShadCor(){
    return R"(
#version 330 core
uniform float u_time;
out vec4 fragColor;
void main() {
    float offset = cos(u_time*10)*0.8;
    float offsin = sin(u_time)*0.2;
    vec3 pos = vec3(offset, offsin, offset);
    vec3 cor = vec3(1.0f, 0.3f, 0.5f);
    fragColor = vec4(cor + pos, 1.0f);
}
)";
}
void triangulo::setFragShader(){
    const char* shader_cor = geraShadCor();
    //cria o objeto
    frangmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //insere código GLSL
    glShaderSource(frangmentShader, 1, &shader_cor, NULL);
    //compila na GPU
    glCompileShader(frangmentShader);
    
    //boa prática
    int success;
    char infoLog[512];
    glGetShaderiv(frangmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(frangmentShader, 512, NULL, infoLog);
        std::cerr << "Erro no Fragment Shader:\n" << infoLog << std::endl;
    } 

}
void triangulo::uneVertFragShader(){
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, frangmentShader);
    glLinkProgram(shaderProgram);
    
    //boa prática
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Erro ao linkar Shader Program:\n" << infoLog << std::endl;
    }

}
// --------
void triangulo::setShaderProgram(){
    setVertexShader();
    setFragShader();
    uneVertFragShader();
    
    // usar programa (não obrigatório aqui, mas útil)
    glUseProgram(shaderProgram);

    // após linkar, podemos deletar os shaders compilados
    glDeleteShader(vertexShader);
    glDeleteShader(frangmentShader);
}

void triangulo::setTimeLoc(){
    timeLoc = glGetUniformLocation(shaderProgram, "u_time");
}

triangulo::triangulo(float* v){
    geraVertices(v);
    geraShader();
    setVAO();
    setVBO();
    configVerxtexs();
    setShaderProgram();
    setTimeLoc();
}
triangulo::triangulo(){
    float v[] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f };
    geraVertices(v);
    geraShader();
    setVAO();
    setVBO();
    configVerxtexs();
    setShaderProgram();
    setTimeLoc();
}
triangulo::~triangulo(){
    if(VAO) glDeleteVertexArrays(1, &VAO);
    if(VBO) glDeleteBuffers(1, &VBO);
    if(shaderProgram) glDeleteProgram(shaderProgram);
}
unsigned int triangulo::getVAO(){
    return VAO;
}
unsigned int triangulo::getVBO(){
    return VBO;
}
void triangulo::usetriangulo(float timeValue){
    glUseProgram(shaderProgram);
    glUniform1f(timeLoc, timeValue);
}
void triangulo::drawTriangulo(int first, int count){
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, first, count);
}

