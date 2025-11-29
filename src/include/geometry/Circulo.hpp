#ifndef CIRCULO_HPP
#define CIRCULO_HPP

#include "Forma.hpp"
#include <cmath>

/**
 * @class Circulo
 * @brief Classe que representa um círculo - forma geométrica perfeitamente redonda
 * 
 * Esta classe herda de Forma e implementa um círculo que pode ser
 * desenhado no OpenGL. O círculo é aproximado usando um polígono regular
 * com muitos lados (segmentos), criado como um leque de triângulos.
 * 
 * Características:
 * - Aproximado por N triângulos (segmentos)
 * - Todos os triângulos compartilham o centro
 * - Quanto mais segmentos, mais suave o círculo
 * - Desenhado usando GL_TRIANGLES
 * 
 * Estrutura dos vértices (exemplo com 6 segmentos):
 *       v2
 *      /  \
 *     /    \
 *   v1 ---- centro ---- v3
 *     \    /
 *      \  /
 *       v6
 * 
 * Cada triângulo: centro, vértice atual, próximo vértice
 * Total de vértices = segmentos × 3
 * 
 * Padrão típico:
 * - 32 segmentos: boa qualidade, performance razoável
 * - 64 segmentos: alta qualidade
 * - 16 segmentos: baixa qualidade, melhor performance
 */
class Circulo : public Forma {
public:
    // ========== Construtores ==========
    
    /**
     * @brief Construtor padrão - cria um círculo com raio e segmentos padrão
     * 
     * @param visualizacao - Objeto visual que define cor e aparência
     * 
     * Cria um círculo centralizado na origem com:
     * - Raio = 0.5
     * - Segmentos = 32 (boa qualidade visual)
     */
    Circulo(visual visualizacao = visual());
    
    /**
     * @brief Construtor com raio customizado
     * 
     * @param raio - Raio do círculo (distância do centro à borda)
     * @param visualizacao - Objeto visual que define cor e aparência
     * 
     * Cria um círculo centralizado com raio especificado.
     * Usa 32 segmentos por padrão.
     */
    Circulo(float raio, visual visualizacao = visual());
    
    /**
     * @brief Construtor com raio e qualidade customizados
     * 
     * @param raio - Raio do círculo
     * @param segmentos - Número de triângulos para aproximar o círculo
     * @param visualizacao - Objeto visual que define cor e aparência
     * 
     * Permite controlar a qualidade visual vs performance:
     * - Menos segmentos = mais rápido, menos suave
     * - Mais segmentos = mais lento, mais suave
     * 
     * Recomendações:
     * - 16-24: círculos pequenos ou distantes
     * - 32-48: uso geral
     * - 64-128: círculos grandes ou com zoom
     */
    Circulo(float raio, int segmentos, visual visualizacao = visual());
    
    /**
     * @brief Construtor com posição, raio e qualidade customizados
     * 
     * @param x - Coordenada x do centro do círculo
     * @param y - Coordenada y do centro do círculo
     * @param raio - Raio do círculo
     * @param segmentos - Número de triângulos para aproximar o círculo
     * @param visualizacao - Objeto visual que define cor e aparência
     * 
     * Cria um círculo em uma posição específica com todos os parâmetros customizados.
     */
    Circulo(float x, float y, float raio, int segmentos, visual visualizacao = visual());
    
    /**
     * @brief Destrutor
     */
    ~Circulo() override = default;

    // ========== Implementação dos Métodos Virtuais Puros ==========
    
    /**
     * @brief Gera os vértices do círculo
     * 
     * Implementa o método virtual puro de Forma.
     * Cria vértices em um padrão circular usando trigonometria:
     * - x = centro_x + raio × cos(ângulo)
     * - y = centro_y + raio × sin(ângulo)
     * 
     * Para cada segmento, cria um triângulo com:
     * 1. Centro do círculo
     * 2. Vértice na borda no ângulo atual
     * 3. Vértice na borda no próximo ângulo
     */
    void gerarVertices() override;
    
    /**
     * @brief Retorna o modo de desenho OpenGL para círculos
     * 
     * @return GLenum - GL_TRIANGLES
     * 
     * O círculo é desenhado como múltiplos triângulos independentes.
     * Alternativa: GL_TRIANGLE_FAN (mais eficiente, mas requer ordem diferente de vértices)
     */
    GLenum getModoDesenho() const override { return GL_TRIANGLES; }
    
    /**
     * @brief Retorna o número de vértices do círculo
     * 
     * @return int - segmentos × 3 (cada triângulo tem 3 vértices)
     */
    int getNumeroVertices() const override { return segmentos * 3; }

    // ========== Métodos de Transformação ==========
    
    /**
     * @brief Define o raio do círculo
     * 
     * @param novoRaio - Novo raio
     * 
     * Atualiza o raio e regenera os vértices.
     * Útil para animações de crescimento/encolhimento.
     */
    void setRaio(float novoRaio);
    
    /**
     * @brief Define a posição do centro do círculo
     * 
     * @param x - Nova coordenada x do centro
     * @param y - Nova coordenada y do centro
     * 
     * Move o círculo para uma nova posição e regenera os vértices.
     */
    void setPosicao(float x, float y);
    
    /**
     * @brief Define o número de segmentos (qualidade)
     * 
     * @param novosSegmentos - Novo número de segmentos (mínimo: 3)
     * 
     * Ajusta a suavidade do círculo.
     * AVISO: Isso realoca memória e pode ser custoso.
     */
    void setSegmentos(int novosSegmentos);
    
    /**
     * @brief Obtém o raio do círculo
     * @return float - Raio atual
     */
    float getRaio() const { return raio; }
    
    /**
     * @brief Obtém o número de segmentos
     * @return int - Número de segmentos usados para desenhar o círculo
     */
    int getSegmentos() const { return segmentos; }
    
    /**
     * @brief Obtém a posição do centro do círculo
     * @param outX - Variável para armazenar a coordenada x
     * @param outY - Variável para armazenar a coordenada y
     */
    void getPosicao(float& outX, float& outY) const {
        outX = centroX;
        outY = centroY;
    }
    
    /**
     * @brief Calcula a área do círculo
     * @return float - Área (π × raio²)
     */
    float calcularArea() const { return M_PI * raio * raio; }
    
    /**
     * @brief Calcula a circunferência (perímetro) do círculo
     * @return float - Circunferência (2 × π × raio)
     */
    float calcularCircunferencia() const { return 2.0f * M_PI * raio; }
    
    /**
     * @brief Calcula o diâmetro do círculo
     * @return float - Diâmetro (2 × raio)
     */
    float calcularDiametro() const { return 2.0f * raio; }

private:
    float centroX;   ///< Coordenada x do centro do círculo
    float centroY;   ///< Coordenada y do centro do círculo
    float raio;      ///< Raio do círculo (distância do centro à borda)
    int segmentos;   ///< Número de triângulos usados para aproximar o círculo
    
    /**
     * @brief Atualiza o buffer de vértices na GPU
     * 
     * Deve ser chamado após modificar os vértices para
     * refletir as mudanças na renderização.
     */
    void atualizarBuffer();
};

#endif // CIRCULO_HPP
