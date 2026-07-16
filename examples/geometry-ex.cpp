#include "init.hpp"
#include "visual.hpp"

#include "geometry/Triangulo.hpp"
#include "geometry/Quadrado.hpp"
#include "geometry/Circulo.hpp"

int main() {
    // Inicializa OpenGL...
    
    // Configura callbacks de erro do GLFW
    identificandoErros();
    
    // Inicializa a biblioteca GLFW
    if(initGLFW() == -1) { 
        std::cerr << "Falha ao inicializar GLFW" << std::endl;
        return -1; 
    }
    
    // Configura hints da janela (versão OpenGL, perfil, etc.)
    hintswindow();
    
    // Cria a janela de renderização
    GLFWwindow* window = glfwCreateWindow(800, 600, "Formas Geométricas", nullptr, nullptr);
    if(testJanela(window) == -1) { 
        std::cerr << "Falha ao criar janela" << std::endl;
        return -1; 
    }

    // Define a janela atual como contexto ativo do OpenGL
    glfwMakeContextCurrent(window);

    // Inicializa GLEW para acessar funções OpenGL modernas
    if(initopenglew() == -1) { 
        std::cerr << "Falha ao inicializar GLEW" << std::endl;
        return -1; 
    }


    // Cria formas
    visual corAzul(cor::blue);
    Triangulo tri(corAzul);
    
    Quadrado quad(0.5f);
    quad.setPosicao(0.5f, 0.5f);
    
    visual corAnimada(cor::rainbow);
    Circulo circ(0.3f, 48, corAnimada);
    circ.setPosicao(-0.5f, -0.5f);
    
    // Loop de renderização
    while (!glfwWindowShouldClose(window)) {
        float tempo = glfwGetTime();
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Desenha todas as formas
        tri.usar(tempo);
        tri.desenhar();
        
        quad.usar(tempo);
        quad.desenhar();
        
        circ.usar(tempo);
        circ.desenhar();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Cleanup automático
    return 0;
}

