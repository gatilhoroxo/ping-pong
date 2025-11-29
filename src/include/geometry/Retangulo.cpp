#include "Retangulo.hpp"

// ========== Construtores ==========

Retangulo::Retangulo(visual visualizacao) 
    : Forma(visualizacao), 
      centroX(0.0f), 
      centroY(0.0f), 
      largura(1.0f), 
      altura(0.6f)
{
    // Cria um retângulo padrão centralizado na origem
    // com proporção largura:altura = 5:3 (similar ao formato 16:10)
    gerarVertices();
    inicializarRecursos();
}

Retangulo::Retangulo(float largura, float altura, visual visualizacao) 
    : Forma(visualizacao), 
      centroX(0.0f), 
      centroY(0.0f), 
      largura(largura), 
      altura(altura)
{
    // Cria um retângulo centralizado com dimensões customizadas
    gerarVertices();
    inicializarRecursos();
}

Retangulo::Retangulo(float x, float y, float largura, float altura, visual visualizacao) 
    : Forma(visualizacao), 
      centroX(x), 
      centroY(y), 
      largura(largura), 
      altura(altura)
{
    // Cria um retângulo em posição e dimensões customizadas
    gerarVertices();
    inicializarRecursos();
}

// ========== Implementação dos Métodos Virtuais ==========

void Retangulo::gerarVertices() {
    // Limpa vértices anteriores
    vertices.clear();
    
    // Reserva espaço para 6 vértices × 2 coordenadas = 12 floats
    vertices.reserve(12);
    
    // Calcula a metade das dimensões para posicionar os cantos
    float meiaLargura = largura / 2.0f;
    float meiaAltura = altura / 2.0f;
    
    // Calcula as coordenadas dos 4 cantos do retângulo
    float esquerda = centroX - meiaLargura;  // x mínimo
    float direita = centroX + meiaLargura;   // x máximo
    float baixo = centroY - meiaAltura;      // y mínimo
    float cima = centroY + meiaAltura;       // y máximo
    
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

void Retangulo::setDimensoes(float novaLargura, float novaAltura) {
    // Atualiza ambas as dimensões
    largura = novaLargura;
    altura = novaAltura;
    
    // Regenera os vértices com as novas dimensões
    gerarVertices();
    
    // Atualiza o buffer na GPU
    atualizarBuffer();
}

void Retangulo::setLargura(float novaLargura) {
    // Atualiza apenas a largura
    largura = novaLargura;
    
    // Regenera os vértices
    gerarVertices();
    
    // Atualiza o buffer na GPU
    atualizarBuffer();
}

void Retangulo::setAltura(float novaAltura) {
    // Atualiza apenas a altura
    altura = novaAltura;
    
    // Regenera os vértices
    gerarVertices();
    
    // Atualiza o buffer na GPU
    atualizarBuffer();
}

void Retangulo::setPosicao(float x, float y) {
    // Atualiza a posição do centro
    centroX = x;
    centroY = y;
    
    // Regenera os vértices na nova posição
    gerarVertices();
    
    // Atualiza o buffer na GPU
    atualizarBuffer();
}

void Retangulo::atualizarBuffer() {
    // Vincula o VBO desta forma
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // Envia os novos dados de vértices para a GPU
    // GL_STATIC_DRAW é apropriado para transformações ocasionais
    // Use GL_DYNAMIC_DRAW se as transformações forem muito frequentes (animações)
    glBufferData(GL_ARRAY_BUFFER, 
                 vertices.size() * sizeof(float), 
                 vertices.data(), 
                 GL_STATIC_DRAW);
}
