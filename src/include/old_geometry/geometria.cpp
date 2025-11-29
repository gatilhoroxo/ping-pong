#include "geometria.hpp"
#include <cmath>

Geometria::Geometria(forma f, glm::vec2 pos, float esc)
    : posicao(pos), escala(esc)
{
    switch (f) {
        case forma::triangulo: geraTriangulo(); break;
        case forma::quadrado: geraQuadrado(); break;
        case forma::circulo: geraCirculo(); break;
    }
}

void Geometria::geraTriangulo() {
    vertices = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.0f,  0.5f
    };
}
void Geometria::geraQuadrado() {
    vertices = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };
}

void Geometria::geraCirculo(int segmentos) {
    float anguloStep = 2.0f * M_PI / segmentos;
    vertices.clear();
    for (int i = 0; i < segmentos; i++) {
        float ang1 = i * anguloStep;
        float ang2 = (i + 1) * anguloStep;
        vertices.push_back(0.0f); vertices.push_back(0.0f); // centro
        vertices.push_back(cos(ang1)); vertices.push_back(sin(ang1));
        vertices.push_back(cos(ang2)); vertices.push_back(sin(ang2));
    }
}
