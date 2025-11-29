/**
 * @file main.cpp
 * @brief Demonstração da arquitetura modular de formas geométricas
 * 
 * Este arquivo demonstra o uso da nova arquitetura orientada a objetos
 * para renderização de formas geométricas usando OpenGL.
 * 
 * Arquitetura:
 * - Classe base abstrata Forma
 * - Classes derivadas: Triangulo, Quadrado, Retangulo, Circulo
 * - Sistema de visualização com cores e shaders
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Sistema de formas geométricas modular
#include "include/geometry/Triangulo.hpp"
#include "include/geometry/Quadrado.hpp"
#include "include/geometry/Retangulo.hpp"
#include "include/geometry/Circulo.hpp"

// Utilitários de inicialização e visualização
#include "include/init.hpp"
#include "include/visual.hpp"

/**
 * @brief Ponto de entrada da aplicação
 * 
 * Fluxo de execução:
 * 1. Inicializa GLFW e cria janela
 * 2. Inicializa GLEW
 * 3. Cria diferentes formas geométricas
 * 4. Loop de renderização
 * 5. Cleanup automático
 */
int main() {
    // ========== INICIALIZAÇÃO ==========
    
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
    
    // ========== CRIAÇÃO DAS FORMAS ==========
    
    std::cout << "\n=== Criando Formas Geométricas ===" << std::endl;
    
    // 1. TRIÂNGULO com vértices customizados e cor azul
    std::cout << "1. Triângulo azul (posição customizada)" << std::endl;
    float verticesTriangulo[] = {
        -0.8f, -0.2f,  // vértice inferior esquerdo
         0.4f, -0.8f,  // vértice inferior direito
         0.0f,  0.4f   // vértice superior
    };
    visual corAzul(cor::blue);
    Triangulo triangulo(verticesTriangulo, corAzul);
    
    // 2. QUADRADO vermelho no canto superior direito
    std::cout << "2. Quadrado vermelho (canto superior direito)" << std::endl;
    visual corVermelha(cor::red);
    Quadrado quadrado(0.3f, corVermelha);
    quadrado.setPosicao(0.5f, 0.5f);
    
    // 3. RETÂNGULO verde no canto inferior esquerdo
    std::cout << "3. Retângulo verde (canto inferior esquerdo)" << std::endl;
    visual corVerde(cor::green);
    Retangulo retangulo(0.4f, 0.25f, corVerde);
    retangulo.setPosicao(-0.5f, -0.5f);
    
    // 4. CÍRCULO com cor animada (rainbow) no centro-esquerda
    std::cout << "4. Círculo animado (centro-esquerda)" << std::endl;
    visual corAnimada(cor::rainbow);
    Circulo circulo(0.2f, 48, corAnimada);  // raio=0.2, 48 segmentos (alta qualidade)
    circulo.setPosicao(-0.5f, 0.3f);
    
    // 5. TRIÂNGULO PADRÃO com cor animada no centro
    std::cout << "5. Triângulo padrão animado (centro)" << std::endl;
    Triangulo trianguloAnimado(corAnimada);
    
    std::cout << "\n=== Iniciando Loop de Renderização ===" << std::endl;
    
    // ========== LOOP DE RENDERIZAÇÃO ==========
    
    while (!glfwWindowShouldClose(window)) {
        // Obtém o tempo atual (para animações)
        float timeValue = glfwGetTime();
        
        // Limpa o buffer de cor com uma cor de fundo roxa
        glClearColor(0.15f, 0.05f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // ===== DESENHA TODAS AS FORMAS =====
        
        // Triângulo azul customizado
        triangulo.usar(timeValue);
        triangulo.desenhar();
        
        // Quadrado vermelho
        quadrado.usar(timeValue);
        quadrado.desenhar();
        
        // Retângulo verde
        retangulo.usar(timeValue);
        retangulo.desenhar();
        
        // Círculo animado
        circulo.usar(timeValue);
        circulo.desenhar();
        
        // Triângulo animado central
        trianguloAnimado.usar(timeValue);
        trianguloAnimado.desenhar();
        
        // Troca os buffers (double buffering)
        glfwSwapBuffers(window);
        
        // Processa eventos (teclado, mouse, etc.)
        glfwPollEvents();
    }
    
    // ========== CLEANUP ==========
    // Os destrutores das formas são chamados automaticamente
    // e liberam todos os recursos OpenGL (VAO, VBO, shaders)
    
    std::cout << "\n=== Encerrando Aplicação ===" << std::endl;
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
