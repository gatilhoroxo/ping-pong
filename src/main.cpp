#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void naufragioErros(int32_t code, const char* txt);

int main() {
    //identificação de erros
    glfwSetErrorCallback(naufragioErros);
    //inicializando
    if (!glfwInit()) { return -1; }

    //gerando janela que vai "pop up" na tela
    GLFWwindow* window = glfwCreateWindow(800, 600, "Janela OpenGL", nullptr, nullptr);
    if (!window) {
        std::cerr << "Erro ao criar a janela\n";
        glfwTerminate();
        return -1;
    }

    //contexto das informações da janela atual
    glfwMakeContextCurrent(window);

    //nao lembro
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //triangulo
    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0,  0.5f
    };

    //nao lembro pra que serve
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
    std::cerr << "Erro ao inicializar GLEW\n";
    return -1;
    }

    //contribui para alguma coisa da amostragem grafica do triangulo
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    //==========================================

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //codigo dos pontos que vao ser ligados e que vao ser mostrados na tela
    const char* shader = R"(
    #version 330 core
    //uniform float u_time;
    layout(location = 0) in vec2 vitor;
    void main() {
        //float offset = cos(u_time*10)*0.5;
        //vec2 pos = vec2(offset, offset);
        gl_Position = vec4(vitor, 0, 1.0);
    }
    )";

    int success;
    char infoLog[512];

    //gera o negocio para poder ser colocado na tela
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &shader, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Erro no Vertex Shader:\n" << infoLog << std::endl;
    }

    //codigo para mudar a cor do objeto que vai ser mostrado
    const char* shader_cor = R"(
    #version 330 core
    uniform float u_time;
    out vec4 fragColor;
    void main() {
        float offset = cos(u_time*10)*0.8;
        float offsin = sin(u_time)*0.2;
        vec3 pos = vec3(offset, offsin, offset);
        vec3 cor = vec3(1.0f, 0.3f, 0.5f);
        fragColor = vec4(cor + pos, 1.0f);
    }
    )";

    //nao sei, acho que tem a ver com os pixels
    unsigned int frangmentShader;
    frangmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frangmentShader, 1, &shader_cor, NULL);
    glCompileShader(frangmentShader);

    glGetShaderiv(frangmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(frangmentShader, 512, NULL, infoLog);
        std::cerr << "Erro no Fragment Shader:\n" << infoLog << std::endl;
    } 

    unsigned int shaderProgram; 
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, frangmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Erro ao linkar Shader Program:\n" << infoLog << std::endl;
    }

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(frangmentShader);

    

    while (!glfwWindowShouldClose(window)) {
        float timeValue = glfwGetTime(); 

        glClearColor(0.3, 0.1, 0.7, 0.8);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        GLint timeLoc = glGetUniformLocation(shaderProgram, "u_time");
        glUniform1f(timeLoc, timeValue);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //quadros
        glfwSwapBuffers(window);

        //acontecimentos na janela
        glfwPollEvents(); //janela ativa
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

//função que mostra o erro
void naufragioErros(int32_t code, const char* txt){
    std::cout << "Morrendo: " << txt << " " << code << "\n";
}
