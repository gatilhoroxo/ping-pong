#ifndef QUADRADO_HPP
#define QUADRADO_HPP

#include "Forma.hpp"

/**
 * @class Quadrado
 * @brief Classe que representa um quadrado - forma geométrica com 4 lados iguais
 * 
 * Esta classe herda de Forma e implementa um quadrado que pode ser
 * desenhado no OpenGL. O quadrado é composto por 2 triângulos (6 vértices).
 * 
 * Características:
 * - 4 cantos, mas 6 vértices (2 triângulos)
 * - Desenhado usando GL_TRIANGLES
 * - Tamanho e posição personalizáveis
 * 
 * Estrutura dos vértices:
 *   v4 -------- v3
 *   |         / |
 *   |       /   |
 *   |     /     |
 *   |   /       |
 *   | /         |
 *   v1 -------- v2
 * 
 * Triângulo 1: v1, v2, v3
 * Triângulo 2: v1, v3, v4
 */
class Quadrado : public Forma {
public:
    // ========== Construtores ==========
    
    /**
     * @brief Construtor padrão - cria um quadrado com tamanho padrão
     * 
     * @param visualizacao - Objeto visual que define cor e aparência
     * 
     * Cria um quadrado centralizado na origem com lado = 1.0
     * Cantos em (-0.5, -0.5) até (0.5, 0.5)
     */
    Quadrado(visual visualizacao = visual());
    
    /**
     * @brief Construtor com tamanho customizado
     * 
     * @param lado - Comprimento do lado do quadrado
     * @param visualizacao - Objeto visual que define cor e aparência
     * 
     * Cria um quadrado centralizado com o tamanho especificado.
     */
    Quadrado(float lado, visual visualizacao = visual());
    
    /**
     * @brief Construtor com posição e tamanho customizados
     * 
     * @param x - Coordenada x do centro do quadrado
     * @param y - Coordenada y do centro do quadrado
     * @param lado - Comprimento do lado do quadrado
     * @param visualizacao - Objeto visual que define cor e aparência
     * 
     * Cria um quadrado em uma posição específica com o tamanho especificado.
     */
    Quadrado(float x, float y, float lado, visual visualizacao = visual());
    
    /**
     * @brief Destrutor
     */
    ~Quadrado() override = default;

    // ========== Implementação dos Métodos Virtuais Puros ==========
    
    /**
     * @brief Gera os vértices do quadrado
     * 
     * Implementa o método virtual puro de Forma.
     * Define os 6 vértices (2 triângulos) que formam o quadrado.
     */
    void gerarVertices() override;
    
    /**
     * @brief Retorna o modo de desenho OpenGL para quadrados
     * 
     * @return GLenum - GL_TRIANGLES
     * 
     * O quadrado é desenhado como 2 triângulos adjacentes.
     */
    GLenum getModoDesenho() const override { return GL_TRIANGLES; }
    
    /**
     * @brief Retorna o número de vértices do quadrado
     * 
     * @return int - 6 (2 triângulos × 3 vértices cada)
     */
    int getNumeroVertices() const override { return 6; }

    // ========== Métodos de Transformação ==========
    
    /**
     * @brief Define o tamanho do quadrado
     * 
     * @param novoLado - Novo comprimento do lado
     * 
     * Atualiza o tamanho do quadrado e regenera os vértices.
     */
    void setTamanho(float novoLado);
    
    /**
     * @brief Define a posição do centro do quadrado
     * 
     * @param x - Nova coordenada x do centro
     * @param y - Nova coordenada y do centro
     * 
     * Move o quadrado para uma nova posição e regenera os vértices.
     */
    void setPosicao(float x, float y);
    
    /**
     * @brief Obtém o tamanho do lado do quadrado
     * @return float - Comprimento do lado
     */
    float getTamanho() const { return lado; }
    
    /**
     * @brief Obtém a posição do centro do quadrado
     * @param outX - Variável para armazenar a coordenada x
     * @param outY - Variável para armazenar a coordenada y
     */
    void getPosicao(float& outX, float& outY) const {
        outX = centroX;
        outY = centroY;
    }

private:
    float centroX;  ///< Coordenada x do centro do quadrado
    float centroY;  ///< Coordenada y do centro do quadrado
    float lado;     ///< Comprimento do lado do quadrado
    
    /**
     * @brief Atualiza o buffer de vértices na GPU
     * 
     * Deve ser chamado após modificar os vértices para
     * refletir as mudanças na renderização.
     */
    void atualizarBuffer();
};

#endif // QUADRADO_HPP
