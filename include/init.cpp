#include "init.hpp"


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
