// Tutorial 01: Abrir uma janela

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main(){
    glewExperimental = true; // Needed for core profile
    if(!glfwInit()){
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(FLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Abrir uma janela e criar o contexto do OpenGL
    GLFWwindow* window; 
    window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
    if(window == NULL){
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // Initialize GLEW

    glewExperimental = true;
    if(glewInit() != GLEW_OK){
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Garanta que nós conseguimos capturar a tecla 'escape' pressionada abaixo
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do{
        // Limpe a tela. "glClear" é usado para limpar o buffer de cor e o buffer de profundidade. 
        glClear(GL_COLOR_BUFFER_BIT);

        // Aqui é onde vocẽ desenharia algo

        // Troca de buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0); // Verifica se a tecla ESC foi pressionada ou se a janeja foi fechada

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}