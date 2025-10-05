#ifndef GEOMETRIA_HPP
#define GEOMETRIA_HPP

#include <vector>
#include <glm/glm.hpp>

enum class forma {
    triangulo,
    quadrado,
    circulo
};

class Geometria {
private:
    std::vector<float> vertices;
    glm::vec2 posicao;
    float escala;

    void geraTriangulo();
    void geraQuadrado();
    void geraCirculo(int segmentos = 32);

public:
    Geometria(forma f = forma::triangulo, glm::vec2 pos = {0.0f, 0.0f}, float esc = 1.0f);

    const std::vector<float>& getVertices() const { return vertices; }
    glm::vec2 getPosicao() const { return posicao; }
    float getEscala() const { return escala; }
};

#endif
