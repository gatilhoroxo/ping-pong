#ifndef RETANGULO_HPP
#define RETANGULO_HPP

#include "Forma.hpp"

/**
 * @class Retangulo
 * @brief Classe que representa um retângulo - forma geométrica com 4 lados, lados opostos iguais
 * 
 * Esta classe herda de Forma e implementa um retângulo que pode ser
 * desenhado no OpenGL. O retângulo é composto por 2 triângulos (6 vértices).
 * 
 * Características:
 * - 4 cantos, mas 6 vértices (2 triângulos)
 * - Largura e altura independentes
 * - Desenhado usando GL_TRIANGLES
 * - Posição e dimensões personalizáveis
 * 
 * Diferença do Quadrado:
 * - Quadrado: lado = lado (todos iguais)
 * - Retângulo: largura ≠ altura (podem ser diferentes)
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
class Retangulo : public Forma {
public:
    // ========== Construtores ==========
    
    /**
     * @brief Construtor padrão - cria um retângulo com dimensões padrão
     * 
     * @param visualizacao - Objeto visual que define cor e aparência
     * 
     * Cria um retângulo centralizado na origem com:
     * - Largura = 1.0
     * - Altura = 0.6
     */
    Retangulo(visual visualizacao = visual());
    
    /**
     * @brief Construtor com dimensões customizadas
     * 
     * @param largura - Largura (extensão horizontal) do retângulo
     * @param altura - Altura (extensão vertical) do retângulo
     * @param visualizacao - Objeto visual que define cor e aparência
     * 
     * Cria um retângulo centralizado com dimensões especificadas.
     */
    Retangulo(float largura, float altura, visual visualizacao = visual());
    
    /**
     * @brief Construtor com posição e dimensões customizadas
     * 
     * @param x - Coordenada x do centro do retângulo
     * @param y - Coordenada y do centro do retângulo
     * @param largura - Largura do retângulo
     * @param altura - Altura do retângulo
     * @param visualizacao - Objeto visual que define cor e aparência
     * 
     * Cria um retângulo em uma posição específica com dimensões especificadas.
     */
    Retangulo(float x, float y, float largura, float altura, visual visualizacao = visual());
    
    /**
     * @brief Destrutor
     */
    ~Retangulo() override = default;

    // ========== Implementação dos Métodos Virtuais Puros ==========
    
    /**
     * @brief Gera os vértices do retângulo
     * 
     * Implementa o método virtual puro de Forma.
     * Define os 6 vértices (2 triângulos) que formam o retângulo.
     */
    void gerarVertices() override;
    
    /**
     * @brief Retorna o modo de desenho OpenGL para retângulos
     * 
     * @return GLenum - GL_TRIANGLES
     * 
     * O retângulo é desenhado como 2 triângulos adjacentes.
     */
    GLenum getModoDesenho() const override { return GL_TRIANGLES; }
    
    /**
     * @brief Retorna o número de vértices do retângulo
     * 
     * @return int - 6 (2 triângulos × 3 vértices cada)
     */
    int getNumeroVertices() const override { return 6; }

    // ========== Métodos de Transformação ==========
    
    /**
     * @brief Define as dimensões do retângulo
     * 
     * @param novaLargura - Nova largura
     * @param novaAltura - Nova altura
     * 
     * Atualiza as dimensões do retângulo e regenera os vértices.
     */
    void setDimensoes(float novaLargura, float novaAltura);
    
    /**
     * @brief Define apenas a largura do retângulo
     * 
     * @param novaLargura - Nova largura
     */
    void setLargura(float novaLargura);
    
    /**
     * @brief Define apenas a altura do retângulo
     * 
     * @param novaAltura - Nova altura
     */
    void setAltura(float novaAltura);
    
    /**
     * @brief Define a posição do centro do retângulo
     * 
     * @param x - Nova coordenada x do centro
     * @param y - Nova coordenada y do centro
     * 
     * Move o retângulo para uma nova posição e regenera os vértices.
     */
    void setPosicao(float x, float y);
    
    /**
     * @brief Obtém a largura do retângulo
     * @return float - Largura atual
     */
    float getLargura() const { return largura; }
    
    /**
     * @brief Obtém a altura do retângulo
     * @return float - Altura atual
     */
    float getAltura() const { return altura; }
    
    /**
     * @brief Obtém a posição do centro do retângulo
     * @param outX - Variável para armazenar a coordenada x
     * @param outY - Variável para armazenar a coordenada y
     */
    void getPosicao(float& outX, float& outY) const {
        outX = centroX;
        outY = centroY;
    }
    
    /**
     * @brief Calcula a área do retângulo
     * @return float - Área (largura × altura)
     */
    float calcularArea() const { return largura * altura; }
    
    /**
     * @brief Calcula o perímetro do retângulo
     * @return float - Perímetro (2 × largura + 2 × altura)
     */
    float calcularPerimetro() const { return 2.0f * (largura + altura); }

private:
    float centroX;   ///< Coordenada x do centro do retângulo
    float centroY;   ///< Coordenada y do centro do retângulo
    float largura;   ///< Largura (extensão horizontal) do retângulo
    float altura;    ///< Altura (extensão vertical) do retângulo
    
    /**
     * @brief Atualiza o buffer de vértices na GPU
     * 
     * Deve ser chamado após modificar os vértices para
     * refletir as mudanças na renderização.
     */
    void atualizarBuffer();
};

#endif // RETANGULO_HPP
