#include "Quadrado.hpp"

// ========== Construtores ==========

Quadrado::Quadrado(visual visualizacao) 
    : Forma(visualizacao), centroX(0.0f), centroY(0.0f), lado(1.0f)
{
    // Cria um quadrado padrão centralizado na origem
    // com lado = 1.0 (de -0.5 a 0.5 em ambos os eixos)
    gerarVertices();
    inicializarRecursos();
}

Quadrado::Quadrado(float lado, visual visualizacao) 
    : Forma(visualizacao), centroX(0.0f), centroY(0.0f), lado(lado)
{
    // Cria um quadrado centralizado com tamanho customizado
    gerarVertices();
    inicializarRecursos();
}

Quadrado::Quadrado(float x, float y, float lado, visual visualizacao) 
    : Forma(visualizacao), centroX(x), centroY(y), lado(lado)
{
    // Cria um quadrado em posição e tamanho customizados
    gerarVertices();
    inicializarRecursos();
}

// ========== Implementação dos Métodos Virtuais ==========

void Quadrado::gerarVertices() {
    // Limpa vértices anteriores
    vertices.clear();
    
    // Reserva espaço para 6 vértices × 2 coordenadas = 12 floats
    vertices.reserve(12);
    
    // Calcula a metade do lado para posicionar os cantos
    float meiLado = lado / 2.0f;
    
    // Calcula as coordenadas dos 4 cantos do quadrado
    float esquerda = centroX - meiLado;  // x mínimo
    float direita = centroX + meiLado;   // x máximo
    float baixo = centroY - meiLado;     // y mínimo
    float cima = centroY + meiLado;      // y máximo
    
    // ===== PRIMEIRO TRIÂNGULO (inferior direito) =====
    // Vértice 1: canto inferior esquerdo
    vertices.push_back(esquerda);
    vertices.push_back(baixo);
    
    // Vértice 2: canto inferior direito
    vertices.push_back(direita);
    vertices.push_back(baixo);
    
    // Vértice 3: canto superior direito
    vertices.push_back(direita);
    vertices.push_back(cima);
    
    // ===== SEGUNDO TRIÂNGULO (superior esquerdo) =====
    // Vértice 1: canto inferior esquerdo (repetido)
    vertices.push_back(esquerda);
    vertices.push_back(baixo);
    
    // Vértice 3: canto superior direito (repetido)
    vertices.push_back(direita);
    vertices.push_back(cima);
    
    // Vértice 4: canto superior esquerdo
    vertices.push_back(esquerda);
    vertices.push_back(cima);
}

// ========== Métodos de Transformação ==========

void Quadrado::setTamanho(float novoLado) {
    // Atualiza o tamanho do lado
    lado = novoLado;
    
    // Regenera os vértices com o novo tamanho
    gerarVertices();
    
    // Atualiza o buffer na GPU
    atualizarBuffer();
}

void Quadrado::setPosicao(float x, float y) {
    // Atualiza a posição do centro
    centroX = x;
    centroY = y;
    
    // Regenera os vértices na nova posição
    gerarVertices();
    
    // Atualiza o buffer na GPU
    atualizarBuffer();
}

void Quadrado::atualizarBuffer() {
    // Vincula o VBO desta forma
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // Envia os novos dados de vértices para a GPU
    // GL_STATIC_DRAW ainda é apropriado mesmo para dados que mudam ocasionalmente
    // Use GL_DYNAMIC_DRAW se as transformações forem muito frequentes
    glBufferData(GL_ARRAY_BUFFER, 
                 vertices.size() * sizeof(float), 
                 vertices.data(), 
                 GL_STATIC_DRAW);
}
