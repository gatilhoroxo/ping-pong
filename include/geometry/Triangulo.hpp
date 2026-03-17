#ifndef TRIANGULO_HPP
#define TRIANGULO_HPP

#include "Forma.hpp"

/**
 * @class Triangulo
 * @brief Classe que representa um triângulo - forma geométrica com 3 vértices
 * 
 * Esta classe herda de Forma e implementa um triângulo que pode ser
 * desenhado no OpenGL. O triângulo é definido por 3 pontos no espaço 2D.
 * 
 * Características:
 * - 3 vértices (6 floats: x1, y1, x2, y2, x3, y3)
 * - Desenhado usando GL_TRIANGLES
 * - Pode usar vértices customizados ou padrão
 */
class Triangulo : public Forma {
public:
    // ========== Construtores ==========
    
    /**
     * @brief Construtor padrão - cria um triângulo com vértices predefinidos
     * 
     * @param visualizacao - Objeto visual que define cor e aparência
     * 
     * Cria um triângulo padrão com vértices em:
     * - (-0.5, -0.5) - vértice inferior esquerdo
     * - ( 0.5, -0.5) - vértice inferior direito
     * - ( 0.0,  0.5) - vértice superior central
     */
    Triangulo(visual visualizacao = visual());
    
    /**
     * @brief Construtor com vértices customizados
     * 
     * @param vertices - Array de 6 floats [x1, y1, x2, y2, x3, y3]
     * @param visualizacao - Objeto visual que define cor e aparência
     * 
     * Permite criar um triângulo com vértices específicos definidos pelo usuário.
     * O array deve conter exatamente 6 valores (3 pares de coordenadas x,y).
     */
    Triangulo(const float vertices[6], visual visualizacao = visual());
    
    /**
     * @brief Destrutor
     * 
     * O destrutor da classe base (Forma) cuida da limpeza dos recursos OpenGL.
     */
    ~Triangulo() override = default;

    // ========== Implementação dos Métodos Virtuais Puros ==========
    
    /**
     * @brief Gera os vértices do triângulo
     * 
     * Implementa o método virtual puro de Forma.
     * Define os 3 vértices do triângulo e popula o vetor vertices.
     * 
     * Este método é chamado durante a construção do objeto.
     */
    void gerarVertices() override;
    
    /**
     * @brief Retorna o modo de desenho OpenGL para triângulos
     * 
     * @return GLenum - GL_TRIANGLES
     * 
     * GL_TRIANGLES desenha triângulos independentes usando grupos de 3 vértices.
     */
    GLenum getModoDesenho() const override { return GL_TRIANGLES; }
    
    /**
     * @brief Retorna o número de vértices do triângulo
     * 
     * @return int - 3 (um triângulo sempre tem 3 vértices)
     */
    int getNumeroVertices() const override { return 3; }

    // ========== Métodos Auxiliares ==========
    
    /**
     * @brief Define vértices customizados para o triângulo
     * 
     * @param vertices - Array de 6 floats [x1, y1, x2, y2, x3, y3]
     * 
     * Permite modificar os vértices do triângulo após a construção.
     * Útil para animações ou transformações.
     */
    void setVerticesCustomizados(const float vertices[6]);

private:
    /// Array auxiliar para armazenar vértices customizados temporariamente
    float verticesCustomizados[6];
    
    /// Flag que indica se o triângulo usa vértices customizados
    bool usarCustomizados;
};

#endif // TRIANGULO_HPP
