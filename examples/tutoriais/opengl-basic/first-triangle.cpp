// Tutorial 02: o primeiro triangulo (vermelho)

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


int baseInit(){
    glewExperimental = true; // Needed for core profile
    if(!glfwInit()){
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

    return 1;
}

int createWindow(GLFWwindow** window){
    *window = glfwCreateWindow( 1024, 768, "Tutorial 02", nullptr, nullptr);
    if(*window == nullptr){
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        glfwTerminate();
        return -1;
    }

    return 1;
}

int checkGlew(){
    glewExperimental = true;
    if(glewInit() != GLEW_OK){
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    return 1;
}

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

int main(){
    if(baseInit() == -1) return -1;

    GLFWwindow* window; 
    if(createWindow(&window) == -1) return -1;

    glfwMakeContextCurrent(window);
    if(checkGlew() == -1) return -1;

    // The VAO
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Lembre-se que o centro da tela é o ponto (0,0,0).
    // Um array com 3 vetores que representam 3 vertices do triangulo. Estão em 3D, mas o Z é 0, então eles estão em um plano 2D
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f, // Vertice 1: x=-1, y=-1, z=0. Fica no canto inferior esquerdo da tela.
        1.0f, -1.0f, 0.0f, // Vertice 2: x=1, y=-1, z=0. Fica no canto inferior direito da tela.
        0.0f, 1.0f, 0.0f  // Vertice 3: x=0, y=1, z=0. Fica no meio da parte superior da tela.
    };

    // Isso é o que chamamos de "Vertex Buffer Object", ou VBO. 
    // Ele é usado para enviar um grande número de vertices para a placa gráfica em uma única chamada.
    // Só precisa ser feito uma vez, depois os buffers podem ser reutilizados para enviar dados para a placa g. a qualquer momento. 
        // Isso vai identificar nosso vertice buffer
        GLuint vertexbuffer;
        // Gera 1 buffer, põe o resultado identificado no vertexbuffer
        glGenBuffers(1, &vertexbuffer);
        // As próximas linhas dirão sobre nosso buffer: que tipo de buffer é, quantos bytes ele tem, onde estão os dados, e como eles devem ser usados
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        // Dando nossos vertices para o OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // Criando e compilando nosso programa GLSL  dos shaders
    GLuint programID = LoadShaders("examples/tutoriais/basic/first-triangle.vertexshader", "examples/tutoriais/basic/first-triangle.fragmentshader");
    if(programID == 0) return -1;


    // Garanta que nós conseguimos capturar a tecla 'escape' pressionada abaixo
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Verifica se a tecla ESC foi pressionada ou se a janeja foi fechada
    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
    {
        glClearColor(0.1f, 0.05f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,          // attribute 0
            3,          // size
            GL_FLOAT,   // type
            GL_FALSE,   // normalized?
            0,          // stride
            (void*)0    // array buffer offset
        );

        // Use nosso shader
        glUseProgram(programID);
        
        // Desenhando o triangulo
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        // Troca de buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){
    // Cria os shaders. Retorna 0 se falhou.
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Lê o código dos shaders a partir dos arquivos
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }else{
        printf("Não foi possível abrir %s. Verifique se o caminho está correto.\n", vertex_file_path);
        getchar();
        return 0;
    }

    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    } else{
        printf("Não foi possível abrir %s. Verifique se o caminho está correto.\n", fragment_file_path);
        getchar();
        return 0;
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compila o shader de vértice
    printf("Compilando shader de vértice: %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , nullptr);
    glCompileShader(VertexShaderID);

    // Verifica o shader de vértice
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    // Compila o shader de fragmento
    printf("Compilando shader de fragmento: %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , nullptr);
    glCompileShader(FragmentShaderID);

    // Verifica o shader de fragmento
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Linka o programa de shader
    printf("Linkando programa\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Verifica o programa de shader
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}
