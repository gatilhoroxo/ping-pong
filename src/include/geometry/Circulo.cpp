#include "Circulo.hpp"
#include <cmath>

// Define M_PI caso não esteja definido
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ========== Construtores ==========

Circulo::Circulo(visual visualizacao) 
    : Forma(visualizacao), 
      centroX(0.0f), 
      centroY(0.0f), 
      raio(0.5f), 
      segmentos(32)
{
    // Cria um círculo padrão centralizado na origem
    // com raio médio e qualidade razoável (32 segmentos)
    gerarVertices();
    inicializarRecursos();
}

Circulo::Circulo(float raio, visual visualizacao) 
    : Forma(visualizacao), 
      centroX(0.0f), 
      centroY(0.0f), 
      raio(raio), 
      segmentos(32)
{
    // Cria um círculo centralizado com raio customizado
    gerarVertices();
    inicializarRecursos();
}

Circulo::Circulo(float raio, int segmentos, visual visualizacao) 
    : Forma(visualizacao), 
      centroX(0.0f), 
      centroY(0.0f), 
      raio(raio), 
      segmentos(segmentos < 3 ? 3 : segmentos) // Mínimo de 3 segmentos
{
    // Cria um círculo com raio e qualidade customizados
    gerarVertices();
    inicializarRecursos();
}

Circulo::Circulo(float x, float y, float raio, int segmentos, visual visualizacao) 
    : Forma(visualizacao), 
      centroX(x), 
      centroY(y), 
      raio(raio), 
      segmentos(segmentos < 3 ? 3 : segmentos) // Mínimo de 3 segmentos
{
    // Cria um círculo totalmente customizado
    gerarVertices();
    inicializarRecursos();
}

// ========== Implementação dos Métodos Virtuais ==========

void Circulo::gerarVertices() {
    // Limpa vértices anteriores
    vertices.clear();
    
    // Reserva espaço: segmentos triângulos × 3 vértices × 2 coordenadas
    vertices.reserve(segmentos * 3 * 2);
    
    // Calcula o incremento angular entre cada segmento
    // 2π radianos (360°) dividido pelo número de segmentos
    float anguloIncremento = (2.0f * M_PI) / static_cast<float>(segmentos);
    
    // Gera um triângulo para cada segmento
    for (int i = 0; i < segmentos; i++) {
        // Calcula os ângulos para os dois vértices da borda deste triângulo
        float angulo1 = i * anguloIncremento;              // Ângulo do vértice atual
        float angulo2 = (i + 1) * anguloIncremento;        // Ângulo do próximo vértice
        
        // ===== TRIÂNGULO: centro + dois pontos consecutivos na borda =====
        
        // Vértice 1: Centro do círculo
        vertices.push_back(centroX);
        vertices.push_back(centroY);
        
        // Vértice 2: Ponto na borda no ângulo1
        // Usa trigonometria para calcular a posição:
        // x = centro_x + raio × cos(ângulo)
        // y = centro_y + raio × sin(ângulo)
        vertices.push_back(centroX + raio * std::cos(angulo1));
        vertices.push_back(centroY + raio * std::sin(angulo1));
        
        // Vértice 3: Ponto na borda no ângulo2 (próximo ponto)
        vertices.push_back(centroX + raio * std::cos(angulo2));
        vertices.push_back(centroY + raio * std::sin(angulo2));
    }
    
    // Após este loop, temos um círculo completo formado por 'segmentos' triângulos
    // que se conectam como fatias de uma pizza
}

// ========== Métodos de Transformação ==========

void Circulo::setRaio(float novoRaio) {
    // Valida que o raio seja positivo
    if (novoRaio <= 0.0f) {
        std::cerr << "AVISO: Raio deve ser positivo. Usando valor absoluto." << std::endl;
        novoRaio = std::abs(novoRaio);
    }
    
    // Atualiza o raio
    raio = novoRaio;
    
    // Regenera os vértices com o novo raio
    gerarVertices();
    
    // Atualiza o buffer na GPU
    atualizarBuffer();
}

void Circulo::setPosicao(float x, float y) {
    // Atualiza a posição do centro
    centroX = x;
    centroY = y;
    
    // Regenera os vértices na nova posição
    gerarVertices();
    
    // Atualiza o buffer na GPU
    atualizarBuffer();
}

void Circulo::setSegmentos(int novosSegmentos) {
    // Valida o número mínimo de segmentos
    if (novosSegmentos < 3) {
        std::cerr << "AVISO: Número mínimo de segmentos é 3. Ajustando..." << std::endl;
        novosSegmentos = 3;
    }
    
    // Atualiza o número de segmentos
    segmentos = novosSegmentos;
    
    // Regenera os vértices com o novo número de segmentos
    // NOTA: Isso pode mudar significativamente a quantidade de memória usada
    gerarVertices();
    
    // Atualiza o buffer na GPU
    // Como o número de vértices mudou, precisamos reenviar tudo
    atualizarBuffer();
}

void Circulo::atualizarBuffer() {
    // Vincula o VBO desta forma
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // Envia os novos dados de vértices para a GPU
    // GL_STATIC_DRAW é apropriado para transformações ocasionais
    // Use GL_DYNAMIC_DRAW se as transformações forem muito frequentes
    glBufferData(GL_ARRAY_BUFFER, 
                 vertices.size() * sizeof(float), 
                 vertices.data(), 
                 GL_STATIC_DRAW);
}
