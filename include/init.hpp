#ifndef INIT
#define INIT
//faz o carregamento das funções do opengl
#include <GL/glew.h>
//lida com a janela, entrada do teclado/mouse e contexto do openGL
#include <GLFW/glfw3.h>
#include <iostream>

void naufragioErros(int32_t code, const char* txt);
void identificandoErros();
int initGLFW();
int testJanela(GLFWwindow* window);
void hintswindow();
int initopenglew();


#endif 