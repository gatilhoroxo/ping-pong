
### 1. **Extensibilidade**
```cpp
// Adicionar nova forma é trivial:
class Pentagono : public Forma {
    void gerarVertices() override { /* implementação */ }
    GLenum getModoDesenho() const override { return GL_TRIANGLES; }
    int getNumeroVertices() const override { return 15; } // 5 triângulos
};
```

### 2. **Polimorfismo**
```cpp
// Você pode tratar todas as formas uniformemente:
std::vector<Forma*> formas;
formas.push_back(new Triangulo());
formas.push_back(new Quadrado());
formas.push_back(new Circulo());

for (auto forma : formas) {
    forma->usar(tempo);
    forma->desenhar();
}
```

### 3. **Encapsulamento**
```cpp
// Cada forma gerencia seus próprios detalhes:
Circulo circ(0.5f, 64);  // Você não precisa saber que usa 64 triângulos
circ.desenhar();         // Internamente usa GL_TRIANGLES, mas você não precisa saber
```

### 4. **Reutilização de Código**
- Toda a lógica de OpenGL (VAO, VBO, shaders) está na classe `Forma`
- Classes derivadas só implementam a geometria específica
- Não há duplicação de código

### 5. **Manutenibilidade**
- Código organizado por responsabilidade
- Fácil localizar e corrigir bugs
- Documentação inline em cada arquivo
