#include "Forma.hpp"

// ========== Construtor e Destrutor ==========

Forma::Forma(visual visualizacao) 
    : vis(visualizacao), 
      VAO(0), 
      VBO(0), 
      shaderProgram(0), 
      vertexShader(0), 
      fragmentShader(0),
      timeLoc(-1)
{
    // Construtor base - inicializa os atributos
    // As classes derivadas devem chamar gerarVertices() e inicializarRecursos()
}

Forma::~Forma() {
    // Libera todos os recursos OpenGL alocados
    if (VAO) {
        glDeleteVertexArrays(1, &VAO);
    }
    if (VBO) {
        glDeleteBuffers(1, &VBO);
    }
    if (shaderProgram) {
        glDeleteProgram(shaderProgram);
    }
}

// ========== Métodos de Configuração OpenGL ==========

void Forma::setVAO() {
    // Gera um novo Vertex Array Object
    glGenVertexArrays(1, &VAO);
    // Vincula (bind) o VAO para torná-lo ativo
    // Todas as configurações subsequentes serão armazenadas neste VAO
    glBindVertexArray(VAO);
}

void Forma::setVBO() {
    // Gera um novo Vertex Buffer Object
    glGenBuffers(1, &VBO);
    // Vincula o VBO ao target GL_ARRAY_BUFFER
    // Este target é usado para dados de vértices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void Forma::configVertices() {
    // Calcula o tamanho total dos dados em bytes
    size_t tamanhoBytes = vertices.size() * sizeof(float);
    
    // Envia os dados dos vértices para o buffer na GPU
    // GL_STATIC_DRAW indica que os dados não mudarão frequentemente
    // Use GL_DYNAMIC_DRAW se os vértices forem animados/modificados
    glBufferData(GL_ARRAY_BUFFER, tamanhoBytes, vertices.data(), GL_STATIC_DRAW);
    
    // Configura como o OpenGL deve interpretar os dados
    // Parâmetros:
    //   0: location do atributo (deve corresponder ao 'layout(location = 0)' no shader)
    //   2: número de componentes por vértice (x, y) - 2D
    //   GL_FLOAT: tipo de dado
    //   GL_FALSE: não normalizar os dados
    //   2 * sizeof(float): stride - distância entre vértices consecutivos
    //   (void*)0: offset - começar do início do buffer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    
    // Ativa o atributo de vértice no location 0
    // O vertex shader poderá acessar este atributo
    glEnableVertexAttribArray(0);
}

void Forma::setVertexShader() {
    // Obtém o código fonte GLSL do vertex shader através do objeto visual
    const char* vertexShaderCode = vis.geraVertexShader();
    
    // Cria um objeto shader do tipo GL_VERTEX_SHADER
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    // Anexa o código fonte ao shader
    // Parâmetros: (shader, número de strings, array de strings, array de tamanhos)
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    
    // Compila o shader na GPU
    glCompileShader(vertexShader);

    // ===== Verificação de erros (boa prática) =====
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERRO: Falha na compilação do Vertex Shader\n" << infoLog << std::endl;
    }
}

void Forma::setFragmentShader() {
    // Obtém o código fonte GLSL do fragment shader através do objeto visual
    const char* fragmentShaderCode = vis.geraFragmentShader();
    
    // Cria um objeto shader do tipo GL_FRAGMENT_SHADER
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Anexa o código fonte ao shader
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    
    // Compila o shader na GPU
    glCompileShader(fragmentShader);
    
    // ===== Verificação de erros (boa prática) =====
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERRO: Falha na compilação do Fragment Shader\n" << infoLog << std::endl;
    }
}

void Forma::linkShaders() {
    // Cria um programa shader vazio
    shaderProgram = glCreateProgram();
    
    // Anexa os shaders compilados ao programa
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    
    // Linka os shaders em um programa executável
    // Isso conecta as saídas do vertex shader com as entradas do fragment shader
    glLinkProgram(shaderProgram);
    
    // ===== Verificação de erros (boa prática) =====
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERRO: Falha ao linkar Shader Program\n" << infoLog << std::endl;
    }
}

void Forma::setShaderProgram() {
    // Compila o vertex shader
    setVertexShader();
    
    // Compila o fragment shader
    setFragmentShader();
    
    // Linka ambos os shaders em um programa
    linkShaders();
    
    // Ativa o programa shader (opcional aqui, mas útil para debug)
    glUseProgram(shaderProgram);

    // Após linkar o programa, podemos deletar os shaders individuais
    // O programa linkado já contém tudo que é necessário
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Forma::setTimeLoc() {
    // Obtém a localização da variável uniform 'u_time' no shader
    // Retorna -1 se a variável não existir ou não for usada
    timeLoc = glGetUniformLocation(shaderProgram, "u_time");
    
    if (timeLoc == -1) {
        // Aviso: u_time não encontrado (pode ser intencional se não houver animação)
        std::cout << "INFO: Uniform 'u_time' não encontrado no shader (pode ser intencional)" << std::endl;
    }
}

void Forma::inicializarRecursos() {
    // Sequência de inicialização dos recursos OpenGL
    // A ordem é importante!
    
    // 1. Criar e vincular o VAO
    setVAO();
    
    // 2. Criar e vincular o VBO
    setVBO();
    
    // 3. Configurar os atributos de vértice e enviar dados
    configVertices();
    
    // 4. Compilar e linkar os shaders
    setShaderProgram();
    
    // 5. Obter a localização das variáveis uniform
    setTimeLoc();
}

// ========== Métodos Públicos de Renderização ==========

void Forma::usar(float timeValue) {
    // Ativa o programa shader desta forma
    glUseProgram(shaderProgram);
    
    // Atualiza a variável uniform u_time se ela existir
    if (timeLoc != -1) {
        glUniform1f(timeLoc, timeValue);
    }
}

void Forma::desenhar() {
    // Vincula o VAO desta forma
    // Isso restaura todas as configurações de atributos de vértice
    glBindVertexArray(VAO);
    
    // Desenha a forma usando os vértices configurados
    // glDrawArrays(modo, primeiro vértice, número de vértices)
    glDrawArrays(getModoDesenho(), 0, getNumeroVertices());
}
