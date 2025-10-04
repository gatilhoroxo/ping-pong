//faz o carregamento das funções do opengl
#include <GL/glew.h>
//lida com a janela, entrada do teclado/mouse e contexto do openGL
#include <GLFW/glfw3.h>
#include <iostream>

#include "include/forms.hpp"

void naufragioErros(int32_t code, const char* txt);
void identificandoErros();
int initGLFW();
int testJanela(GLFWwindow* window);
void hintswindow();
int initopenglew();

int main() {
    identificandoErros();
    if(initGLFW() == -1) { return -1; }

    hintswindow();

    //gerando janela que vai "pop up" na tela
    GLFWwindow* window = glfwCreateWindow(800, 600, "Janela OpenGL", nullptr, nullptr);
    if(testJanela(window) == -1) { return -1; };

    //janela atual será o contexto ativo do openGL
    glfwMakeContextCurrent(window);

    //view port
    /*
    int fw, fh;
    glfwGetFramebufferSize(window, &fw, &fh);
    glViewport(0, 0, fw, fh);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    */

    if(initopenglew() == -1) { return -1; }
    
    float v[] = {
        -0.8f, -0.2f,
        0.4f, -0.8f,
        0.0f,  0.4f
    };
    triangulo par;
    triangulo tri(v);

    //location do uniform pega uma vez apenas

    while (!glfwWindowShouldClose(window)) {
        float timeValue = glfwGetTime(); 

        glClearColor(0.3, 0.1, 0.7, 0.8);
        glClear(GL_COLOR_BUFFER_BIT);

        //*
        par.usetriangulo(timeValue);
        par.drawTriangulo(0, 3);
        //*/
        tri.usetriangulo(timeValue);
        tri.drawTriangulo(0, 3);

        //quadros
        glfwSwapBuffers(window);

        //acontecimentos na janela
        glfwPollEvents(); //janela ativa
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
/*====================================================================*/

//função que mostra o erro
void naufragioErros(int32_t code, const char* txt){
    std::cout << "Morrendo: " << txt << " " << code << "\n";
}

//identificação de erros
void identificandoErros(){
    glfwSetErrorCallback(naufragioErros);
}

//inicializando e criando a janela 
//precisa ser chamada antes de qualquer função GLFW
int initGLFW(){
    if (!glfwInit()) { return -1; } 
    return 0;
}

//verificar se deu certo
int testJanela(GLFWwindow* window){
    if (!window) {
        std::cerr << "Erro ao criar a janela\n";
        glfwTerminate();
        return -1;
    }
    return 0;
}

//hints de contexto
//ao que parece não tem efeito se estiverem depois da criação da janela
void hintswindow(){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

//carrega os ponteiros das funções openGL
//chamar esse depois de criar o contexto
int initopenglew(){
    //permite o uso de extensões modernas, mesmo as não oficiais
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Erro ao inicializar GLEW\n";
        return -1;
    }
    return 0;
}
