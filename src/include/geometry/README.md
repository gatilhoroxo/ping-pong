# Sistema de Formas Geométricas - Arquitetura Modular

## 📐 Visão Geral

Este sistema implementa uma arquitetura orientada a objetos para renderização de formas geométricas usando OpenGL. A arquitetura é baseada em **herança e polimorfismo**, permitindo fácil extensão para novas formas.

## 🏗️ Arquitetura

### Padrões de Design Utilizados

1. **Template Method Pattern**: A classe `Forma` define o esqueleto do algoritmo de inicialização
2. **Strategy Pattern**: Cada forma implementa sua própria estratégia de geração de vértices
3. **Factory Method Pattern**: Cada classe derivada "fabrica" seus próprios vértices

### Hierarquia de Classes

```
Forma (classe abstrata)
├── Triangulo
├── Quadrado
├── Retangulo
└── Circulo
```

## 📁 Estrutura de Arquivos

```
src/include/geometry/
├── Forma.hpp          # Interface abstrata base
├── Forma.cpp          # Implementação comum
├── Triangulo.hpp      # Classe Triangulo
├── Triangulo.cpp      # Implementação Triangulo
├── Quadrado.hpp       # Classe Quadrado
├── Quadrado.cpp       # Implementação Quadrado
├── Retangulo.hpp      # Classe Retangulo
├── Retangulo.cpp      # Implementação Retangulo
├── Circulo.hpp        # Classe Circulo
└── Circulo.cpp        # Implementação Circulo
```

## 🎯 Classe Base: Forma

### Responsabilidades

- Gerenciar recursos OpenGL (VAO, VBO, shaders)
- Fornecer interface comum para todas as formas
- Implementar métodos de renderização genéricos

### Métodos Virtuais Puros

Toda classe derivada **DEVE** implementar:

```cpp
virtual void gerarVertices() = 0;           // Gera vértices específicos
virtual GLenum getModoDesenho() const = 0;  // Retorna GL_TRIANGLES, etc.
virtual int getNumeroVertices() const = 0;  // Retorna número de vértices
```

### Métodos Públicos

```cpp
void usar(float timeValue);  // Ativa shader e atualiza uniforms
void desenhar();             // Renderiza a forma
```

## 📦 Classes Derivadas

### 1️⃣ Triangulo

**Características:**
- 3 vértices (6 floats)
- Modo: `GL_TRIANGLES`
- Vértices customizáveis

**Construtores:**
```cpp
Triangulo();                               // Triângulo padrão
Triangulo(float vertices[6]);              // Vértices customizados
Triangulo(visual visualizacao);            // Com visual específico
```

**Uso:**
```cpp
Triangulo tri;                             // Padrão
float v[] = {-0.5, -0.5, 0.5, -0.5, 0.0, 0.5};
Triangulo triCustom(v);                    // Customizado
```

---

### 2️⃣ Quadrado

**Características:**
- 4 cantos, 6 vértices (2 triângulos)
- Modo: `GL_TRIANGLES`
- Lados iguais

**Construtores:**
```cpp
Quadrado();                                // lado = 1.0, centro = (0,0)
Quadrado(float lado);                      // lado customizado
Quadrado(float x, float y, float lado);    // posição e tamanho
```

**Métodos:**
```cpp
void setTamanho(float lado);
void setPosicao(float x, float y);
float getTamanho();
```

**Uso:**
```cpp
Quadrado quad(0.5f);                       // Quadrado de lado 0.5
quad.setPosicao(0.2f, 0.3f);               // Move para (0.2, 0.3)
quad.setTamanho(0.8f);                     // Redimensiona
```

---

### 3️⃣ Retangulo

**Características:**
- 4 cantos, 6 vértices (2 triângulos)
- Modo: `GL_TRIANGLES`
- Largura e altura independentes

**Construtores:**
```cpp
Retangulo();                                        // 1.0 × 0.6
Retangulo(float largura, float altura);             // Dimensões customizadas
Retangulo(float x, float y, float w, float h);      // Posição e dimensões
```

**Métodos:**
```cpp
void setDimensoes(float largura, float altura);
void setLargura(float largura);
void setAltura(float altura);
void setPosicao(float x, float y);
float calcularArea();                               // largura × altura
float calcularPerimetro();                          // 2(w + h)
```

**Uso:**
```cpp
Retangulo ret(0.8f, 0.4f);                 // 0.8 de largura, 0.4 de altura
ret.setPosicao(-0.2f, 0.1f);               // Move
ret.setAltura(0.6f);                       // Só muda altura
float area = ret.calcularArea();           // Calcula área
```

---

### 4️⃣ Circulo

**Características:**
- Aproximado por N triângulos
- Modo: `GL_TRIANGLES`
- Qualidade ajustável (segmentos)

**Construtores:**
```cpp
Circulo();                                          // raio=0.5, 32 segmentos
Circulo(float raio);                                // raio customizado
Circulo(float raio, int segmentos);                 // raio e qualidade
Circulo(float x, float y, float r, int segs);      // completo
```

**Métodos:**
```cpp
void setRaio(float raio);
void setPosicao(float x, float y);
void setSegmentos(int segmentos);                   // Ajusta qualidade
float calcularArea();                               // π × r²
float calcularCircunferencia();                     // 2π × r
float calcularDiametro();                           // 2 × r
```

**Uso:**
```cpp
Circulo circ(0.3f, 64);                    // Raio 0.3, alta qualidade
circ.setPosicao(0.5f, -0.2f);              // Move
circ.setRaio(0.4f);                        // Muda raio
float area = circ.calcularArea();          // Calcula área
```

**Qualidade vs Performance:**
- 16 segmentos: Baixa qualidade, rápido
- 32 segmentos: Boa qualidade (padrão)
- 64 segmentos: Alta qualidade
- 128+ segmentos: Muito suave, mais lento

---

## 🎨 Sistema Visual

As formas usam a classe `visual` para definir aparência:

```cpp
visual vis(cor::blue);               // Cor azul
Triangulo tri(vis);                  // Triângulo azul

visual animado(cor::rainbow);        // Cor animada
Circulo circ(0.5f, 32, animado);     // Círculo com cor animada
```

**Cores disponíveis:**
- `cor::red`, `cor::blue`, `cor::green`
- `cor::yellow`, `cor::orange`
- `cor::white`, `cor::black`, `cor::gray`
- `cor::rainbow` (animada)

---

## 🚀 Fluxo de Renderização

### 1. Criação
```cpp
Triangulo tri;  // Chama: construtor → gerarVertices() → inicializarRecursos()
```

### 2. Loop de Renderização
```cpp
float tempo = glfwGetTime();

tri.usar(tempo);     // Ativa shader, atualiza uniforms
tri.desenhar();      // Renderiza na tela
```

### 3. Limpeza
```cpp
// Automática no destrutor:
// - Libera VAO
// - Libera VBO
// - Libera shaders
```

---

## 🔧 Exemplo Completo

```cpp
#include "geometry/Triangulo.hpp"
#include "geometry/Quadrado.hpp"
#include "geometry/Circulo.hpp"

int main() {
    // Inicializa OpenGL...
    
    // Cria formas
    visual corAzul(cor::blue);
    Triangulo tri(corAzul);
    
    Quadrado quad(0.5f);
    quad.setPosicao(0.5f, 0.5f);
    
    visual corAnimada(cor::rainbow);
    Circulo circ(0.3f, 48, corAnimada);
    circ.setPosicao(-0.5f, -0.5f);
    
    // Loop de renderização
    while (!glfwWindowShouldClose(window)) {
        float tempo = glfwGetTime();
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Desenha todas as formas
        tri.usar(tempo);
        tri.desenhar();
        
        quad.usar(tempo);
        quad.desenhar();
        
        circ.usar(tempo);
        circ.desenhar();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Cleanup automático
    return 0;
}
```

---

## ➕ Adicionando Novas Formas

Para criar uma nova forma geométrica:

### 1. Crie o Header (.hpp)

```cpp
#ifndef MINHAFORMA_HPP
#define MINHAFORMA_HPP

#include "Forma.hpp"

class MinhaForma : public Forma {
public:
    MinhaForma(visual visualizacao = visual());
    ~MinhaForma() override = default;
    
    void gerarVertices() override;
    GLenum getModoDesenho() const override;
    int getNumeroVertices() const override;
};

#endif
```

### 2. Implemente (.cpp)

```cpp
#include "MinhaForma.hpp"

MinhaForma::MinhaForma(visual visualizacao) : Forma(visualizacao) {
    gerarVertices();
    inicializarRecursos();
}

void MinhaForma::gerarVertices() {
    vertices.clear();
    // Adicione seus vértices aqui
    vertices.push_back(x1); vertices.push_back(y1);
    vertices.push_back(x2); vertices.push_back(y2);
    // ...
}

GLenum MinhaForma::getModoDesenho() const {
    return GL_TRIANGLES; // ou GL_LINES, GL_TRIANGLE_FAN, etc.
}

int MinhaForma::getNumeroVertices() const {
    return vertices.size() / 2; // número de pares (x,y)
}
```

### 3. Use sua forma

```cpp
MinhaForma forma;
forma.usar(tempo);
forma.desenhar();
```

---

## 📝 Boas Práticas

### ✅ Fazer

- Chamar `gerarVertices()` antes de `inicializarRecursos()`
- Usar `atualizarBuffer()` após modificar vértices
- Liberar recursos no destrutor (já implementado na base)
- Validar parâmetros (raio positivo, mínimo de segmentos, etc.)

### ❌ Evitar

- Modificar `vertices` diretamente sem chamar `atualizarBuffer()`
- Criar muitos objetos no loop de renderização
- Usar muitos segmentos em círculos pequenos
- Esquecer de chamar `usar()` antes de `desenhar()`

---

## 🐛 Debug

### Forma não aparece?

1. Verifique se `gerarVertices()` foi chamado
2. Confirme que `inicializarRecursos()` foi executado
3. Verifique se `usar()` é chamado antes de `desenhar()`
4. Confirme que os vértices estão no range [-1, 1]

### Performance ruim?

1. Reduza o número de segmentos em círculos
2. Use `GL_STATIC_DRAW` para formas estáticas
3. Minimize chamadas a `atualizarBuffer()`
4. Agrupe desenhos de formas similares

---

## 📚 Recursos OpenGL Usados

- **VAO (Vertex Array Object)**: Armazena configuração de atributos
- **VBO (Vertex Buffer Object)**: Armazena vértices na GPU
- **Shaders**: Vertex e Fragment shaders para renderização
- **Uniforms**: Variável `u_time` para animações

---

## 🎓 Conceitos Matemáticos

### Triângulo
- 3 vértices definem um plano único
- Base da maioria das formas 3D

### Quadrado/Retângulo
- Decompostos em 2 triângulos
- 6 vértices (alguns duplicados)

### Círculo
- Aproximado por polígono regular
- Vértices calculados via trigonometria:
  - `x = r × cos(θ)`
  - `y = r × sin(θ)`
- Quanto mais segmentos, mais suave

---

## 📄 Licença

Este código é fornecido como está para fins educacionais.

---

## 👥 Contribuindo

Para adicionar novas formas:
1. Herde de `Forma`
2. Implemente os 3 métodos virtuais puros
3. Adicione ao Makefile
4. Documente neste README

---

**Última atualização:** 29 de novembro de 2025
