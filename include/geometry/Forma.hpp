#ifndef FORMA_HPP
#define FORMA_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "../visual.hpp"

/**
 * @class Forma
 * @brief Classe abstrata que serve como interface para todas as formas geométricas
 * 
 * Esta classe define a interface comum que todas as formas geométricas devem implementar.
 * Ela gerencia os recursos do OpenGL (VAO, VBO, shaders) e fornece métodos virtuais puros
 * que cada forma derivada deve implementar para gerar seus vértices específicos.
 * 
 * Padrão de Design: Template Method + Strategy
 * - Template Method: O fluxo de inicialização é definido aqui
 * - Strategy: Cada forma implementa sua própria estratégia de geração de vértices
 */
class Forma {
protected:
    // ========== Atributos de Dados Geométricos ==========
    std::vector<float> vertices;  ///< Vetor dinâmico contendo as coordenadas dos vértices (x, y)
    visual vis;                    ///< Objeto que controla a aparência visual (cor, textura, shaders)
    
    // ========== Recursos OpenGL ==========
    unsigned int VAO;              ///< Vertex Array Object - guarda o estado das configurações de atributos
    unsigned int VBO;              ///< Vertex Buffer Object - armazena vértices na memória da GPU
    unsigned int shaderProgram;    ///< Programa shader compilado e linkado
    unsigned int vertexShader;     ///< Shader de vértices compilado
    unsigned int fragmentShader;   ///< Shader de fragmentos compilado
    GLint timeLoc;                 ///< Localização da variável uniform u_time nos shaders

    // ========== Métodos Privados de Configuração OpenGL ==========
    
    /**
     * @brief Cria e configura o Vertex Array Object (VAO)
     * 
     * O VAO armazena o estado de configuração dos atributos de vértice,
     * permitindo trocar entre diferentes configurações rapidamente.
     */
    void setVAO();
    
    /**
     * @brief Cria e configura o Vertex Buffer Object (VBO)
     * 
     * O VBO aloca memória na GPU e armazena os dados dos vértices
     * para renderização eficiente.
     */
    void setVBO();
    
    /**
     * @brief Configura como o OpenGL deve interpretar os dados dos vértices
     * 
     * Define o layout dos atributos de vértice (posição, normal, etc.)
     * e envia os dados do vetor vertices para o buffer na GPU.
     */
    void configVertices();
    
    /**
     * @brief Compila o vertex shader a partir do código GLSL
     * 
     * O vertex shader processa cada vértice individualmente,
     * transformando suas coordenadas conforme necessário.
     */
    void setVertexShader();
    
    /**
     * @brief Compila o fragment shader a partir do código GLSL
     * 
     * O fragment shader determina a cor final de cada pixel
     * da forma renderizada.
     */
    void setFragmentShader();
    
    /**
     * @brief Une (link) os shaders em um programa shader completo
     * 
     * Cria o programa shader e anexa os vertex e fragment shaders
     * compilados, gerando um pipeline gráfico funcional.
     */
    void linkShaders();
    
    /**
     * @brief Cria o programa shader completo
     * 
     * Orquestra a compilação e linkagem de todos os shaders.
     * Este é um método template que define o fluxo de criação.
     */
    void setShaderProgram();
    
    /**
     * @brief Obtém a localização da variável uniform u_time
     * 
     * A variável u_time permite criar animações baseadas em tempo
     * dentro dos shaders.
     */
    void setTimeLoc();
    
    /**
     * @brief Inicializa todos os recursos OpenGL para a forma
     * 
     * Chama todos os métodos de configuração na ordem correta.
     * Este método é chamado pelos construtores das classes derivadas.
     */
    void inicializarRecursos();

public:
    // ========== Métodos Virtuais Puros (Devem ser implementados pelas classes derivadas) ==========
    
    /**
     * @brief Gera os vértices específicos da forma geométrica
     * 
     * Cada forma derivada implementa este método para calcular
     * seus próprios vértices (triângulo tem 3 vértices, quadrado tem 6, etc.)
     * 
     * @note Este método é virtual puro (= 0), tornando Forma uma classe abstrata
     */
    virtual void gerarVertices() = 0;
    
    /**
     * @brief Obtém o modo de desenho OpenGL apropriado para a forma
     * 
     * @return GLenum - GL_TRIANGLES, GL_TRIANGLE_FAN, GL_LINE_LOOP, etc.
     * 
     * Diferentes formas podem ser desenhadas de maneiras diferentes:
     * - Triângulos: GL_TRIANGLES
     * - Círculos: GL_TRIANGLE_FAN
     * - Linhas: GL_LINE_LOOP
     */
    virtual GLenum getModoDesenho() const = 0;
    
    /**
     * @brief Retorna o número de vértices da forma
     * 
     * @return int - Quantidade de vértices a serem desenhados
     */
    virtual int getNumeroVertices() const = 0;

    // ========== Construtores e Destrutor ==========
    
    /**
     * @brief Construtor padrão
     * 
     * @param visualizacao - Objeto visual que define cor e aparência
     * 
     * Inicializa a forma com uma visualização específica.
     * As classes derivadas devem chamar gerarVertices() e
     * inicializarRecursos() após este construtor.
     */
    Forma(visual visualizacao = visual());
    
    /**
     * @brief Destrutor virtual
     * 
     * Libera todos os recursos OpenGL alocados (VAO, VBO, shaders).
     * Sendo virtual, garante que o destrutor da classe derivada
     * seja chamado corretamente.
     */
    virtual ~Forma();

    // ========== Métodos Públicos de Renderização ==========
    
    /**
     * @brief Ativa o shader program e atualiza uniforms
     * 
     * @param timeValue - Tempo atual para animações
     * 
     * Deve ser chamado antes de desenhar a forma para garantir
     * que o shader correto está ativo e as variáveis uniform atualizadas.
     */
    void usar(float timeValue);
    
    /**
     * @brief Desenha a forma na tela
     * 
     * Vincula o VAO e chama glDrawArrays com os parâmetros apropriados
     * para renderizar a forma geométrica.
     */
    void desenhar();

    // ========== Getters ==========
    
    /**
     * @brief Obtém o Vertex Array Object
     * @return unsigned int - ID do VAO
     */
    unsigned int getVAO() const { return VAO; }
    
    /**
     * @brief Obtém o Vertex Buffer Object
     * @return unsigned int - ID do VBO
     */
    unsigned int getVBO() const { return VBO; }
    
    /**
     * @brief Obtém o programa shader
     * @return unsigned int - ID do shader program
     */
    unsigned int getShaderProgram() const { return shaderProgram; }
    
    /**
     * @brief Obtém o vetor de vértices
     * @return const std::vector<float>& - Referência constante ao vetor de vértices
     */
    const std::vector<float>& getVertices() const { return vertices; }
};

#endif // FORMA_HPP
