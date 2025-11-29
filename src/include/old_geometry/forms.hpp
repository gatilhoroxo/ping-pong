#ifndef TRIANGULO_HPP
#define TRIANGULO_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "visual.hpp"

class triangulo {
private:
    float vertices[6];
    visual vis;
    unsigned int VAO = 0; //vertex array object, guarda o estado das configurações de atributos de vértices
    unsigned int VBO = 0; //vertex buffers object, armazena vértices na memória da GPU
    unsigned int shaderProgram = 0; 
    unsigned int vertexShader = 0; //objeto shader
    unsigned int frangmentShader = 0; //objeto shader
    GLint timeLoc;

    void geraVertices(float* v);
    void setVAO();
    void setVBO();
    void configVerxtexs();
    void setVertexShader();
    void setFragShader();
    void uneVertFragShader();
    void setShaderProgram();
    void setTimeLoc();

public:
    triangulo();
    triangulo(float* v);
    triangulo(visual ct);
    triangulo(float* v, visual ct);
    ~triangulo();
    unsigned int getVAO();
    unsigned int getVBO();
    unsigned int getShaderProgram();
    void usetriangulo(float timeValue);
    void drawTriangulo(int first, int count);
};



#endif
