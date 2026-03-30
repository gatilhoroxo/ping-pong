
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

//função que mostra o erro
void naufragioErros(int32_t code, const char* txt){
    std::cout << "Morrendo: " << txt << " " << code << "\n";
}

int main() {
    // ========== INICIALIZAÇÃO ==========
    
    // Configura callbacks de erro do GLFW
    glfwSetErrorCallback(naufragioErros);
    
    // Inicializa a biblioteca GLFW
    if (!glfwInit()){ 
        std::cerr << "Falha ao inicializar GLFW" << std::endl;
        std::cout << glewGetErrorString(errno) << std::endl;
        return -1; 
    }
    
    // Configura hints da janela (versão OpenGL, perfil, etc.)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(800, 600, "Formas Geométricas", nullptr, nullptr);
    if (!window) {
        std::cerr << "Falha ao criar janela" << std::endl;
        glfwTerminate();
        return -1; 
    }

    // Define a janela atual como contexto ativo do OpenGL
    glfwMakeContextCurrent(window);

    // Inicializa GLEW para acessar funções OpenGL modernas
    glewExperimental = GL_TRUE;
    GLenum err = glewInit(); // Capture o retorno aqui
    if (GLEW_OK != err) {
        std::cerr << "Erro ao inicializar GLEW\n" << glewGetErrorString(err) << std::endl;
        return -1;
    }


    while (!glfwWindowShouldClose(window)) {
        // Obtém o tempo atual (para animações)
        float timeValue = glfwGetTime();
        
        // Limpa o buffer de cor com uma cor de fundo roxa
        glClearColor(0.15f, 0.05f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Troca os buffers (double buffering)
        glfwSwapBuffers(window);
        
        // Processa eventos (teclado, mouse, etc.)
        glfwPollEvents();
    }

    std::cout << "\n=== Encerrando Aplicação ===" << std::endl;
    
    glfwDestroyWindow(window);
    glfwTerminate();
    

}