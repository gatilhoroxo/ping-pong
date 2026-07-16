#include "Triangulo.hpp"
#include <cstring> // para memcpy

// ========== Construtores ==========

Triangulo::Triangulo(visual visualizacao) 
    : Forma(visualizacao), usarCustomizados(false)
{
    // Inicializa com vértices padrão (não customizados)
    // Chama gerarVertices() para criar o triângulo padrão
    gerarVertices();
    
    // Inicializa todos os recursos OpenGL (VAO, VBO, shaders, etc.)
    inicializarRecursos();
}

Triangulo::Triangulo(const float vertices[6], visual visualizacao) 
    : Forma(visualizacao), usarCustomizados(true)
{
    // Copia os vértices customizados fornecidos pelo usuário
    // memcpy é eficiente para copiar arrays de tipos primitivos
    std::memcpy(verticesCustomizados, vertices, 6 * sizeof(float));
    
    // Gera o triângulo com os vértices customizados
    gerarVertices();
    
    // Inicializa todos os recursos OpenGL
    inicializarRecursos();
}

// ========== Implementação dos Métodos Virtuais ==========

void Triangulo::gerarVertices() {
    // Limpa qualquer vértice anterior
    vertices.clear();
    
    // Reserva espaço para 6 floats (3 vértices × 2 coordenadas)
    // Isso evita realocações desnecessárias
    vertices.reserve(6);
    
    if (usarCustomizados) {
        // Usa os vértices customizados fornecidos pelo usuário
        for (int i = 0; i < 6; i++) {
            vertices.push_back(verticesCustomizados[i]);
        }
    } else {
        // Define os vértices padrão do triângulo
        // Forma um triângulo isósceles centralizado
        
        // Vértice 1: inferior esquerdo (-0.5, -0.5)
        vertices.push_back(-0.5f);
        vertices.push_back(-0.5f);
        
        // Vértice 2: inferior direito (0.5, -0.5)
        vertices.push_back(0.5f);
        vertices.push_back(-0.5f);
        
        // Vértice 3: superior central (0.0, 0.5)
        vertices.push_back(0.0f);
        vertices.push_back(0.5f);
    }
}

// ========== Métodos Auxiliares ==========

void Triangulo::setVerticesCustomizados(const float novosVertices[6]) {
    // Marca que estamos usando vértices customizados
    usarCustomizados = true;
    
    // Copia os novos vértices
    std::memcpy(verticesCustomizados, novosVertices, 6 * sizeof(float));
    
    // Regenera os vértices com os novos valores
    gerarVertices();
    
    // Atualiza o VBO na GPU com os novos dados
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), 
                 vertices.data(), GL_STATIC_DRAW);
}
