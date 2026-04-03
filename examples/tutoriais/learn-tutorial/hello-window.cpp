// Getting started: criando uma janela

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(){
    glewExperimental = true;
    if(!glfwInit()){
        fprintf(stderr, "Falha em inicializar o GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1024, 768, "Janela", nullptr, nullptr);
    if(window == nullptr){
        fprintf(stderr, "Falha em criar a janela GLFW");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    if(glewInit() != GLEW_OK){
        fprintf(stderr, "Falha em inicializar o GLEW\n");
        return -1;
    }

    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glClearColor(0.1f, 0.05f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}