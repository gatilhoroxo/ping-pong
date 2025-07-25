## Visão Geral do Projeto

- Objeto completo
    - Dar vida a um ponto branco numa janela vazia. 
    Aprender a gostar de aprender de novo.
- Por que esse projeto é relevante?
    - Para a prática da criatividade abatida.
- Quais são os módulos/partes dele?
    - Apenas um joguinho.
- Como o projeto se comporta no fim? (print/gif/foto)
    - Como um jogo colorido.

## Pré-requisitos

- Requisitos de sistema
    - Linux/WSL (foi o que eu usei)
    - glew, glfw, opengl (bibliotecas)
    - vscode
- Requisitos de conhecimentos
    - Noções de programação em cpp
    - Saber o básico do terminal wsl

## Instalação e Setup

```bash
sudo apt update
sudo apt upgrade

sudo apt install libglfw3-dev
sudo apt install libgl1-mesa-dev libglu1-mesa-devfreeflut3-dev
sudo apt install libglew-dev

# teve um erro de segmentation fault (core dumped) 
# por um tempo e por eu estar usando o wsl preciso fazer isso
export MESA_LOADER_DRIVER_OVERRIDE=egl_swiftshader
export LIBGL_ALWAYS_SOFTWARE=1

```

Compilação

```bash
g++ file.cpp -o app -std=c++17 -lglfw -lGLEW -lGL
./app
```

## Organização de arquivos

```markdown
📁 projeto/
├── src       
├		 └── main.cpp # Código principal
├── makefile      # Script de compilação
└── doc/          # Documentação e anotações
```

## Passo a Passo

### Etapa 1: Aprender como usar OpenGL

- [ ]  Gerar uma janela
- [ ]  Mudar a cor da janela
- [ ]  Desenhar um triangulo na janela
- [ ]  Movimentar o triangulo
- [ ]  Fazer várias cores passar no triangulo

…

<details> 
<summary> o que aprendi </summary>

</details>

<details> 
<summary> erros e soluções </summary>

</details>


### Etapa 2: Fazer o ping

- [ ]  Bolinha mexendo

### Etapa 3: E o pong 

- [ ]  Barrinhas mexendo

## Anotações Extras

- Recursos úteis
- Trechos de códigos alternativos
- Comandos que você sempre esquece
- Atalhos e truques