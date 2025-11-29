#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "include/old_geometry/forms.hpp"
#include "include/init.hpp"

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
    visual cor(cor::blue);
    triangulo par(cor);
    visual c(cor::rainbow);
    triangulo tri(v,c);

    //location do uniform pega uma vez apenas

    while (!glfwWindowShouldClose(window)) {
        float timeValue = glfwGetTime(); 

        glClearColor(0.3, 0.1, 0.7, 0.8);
        glClear(GL_COLOR_BUFFER_BIT);

        //*
        par.usetriangulo(timeValue);
        par.drawTriangulo(0, 3);
        //*///*
        tri.usetriangulo(timeValue);
        tri.drawTriangulo(0, 3);
        //*/
        //quadros
        glfwSwapBuffers(window);

        //acontecimentos na janela
        glfwPollEvents(); //janela ativa
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
