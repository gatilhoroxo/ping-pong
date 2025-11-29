src=src/main.cpp
exe=app

cpp_v=c++17

opengl_flags=-lglfw -lGLEW -lGL
include_paths=-I/usr/include -Isrc/include

# Arquivos da arquitetura de formas geométricas
geometry_src=src/include/geometry/Forma.cpp \
             src/include/geometry/Triangulo.cpp \
             src/include/geometry/Quadrado.cpp \
             src/include/geometry/Retangulo.cpp \
             src/include/geometry/Circulo.cpp

# Arquivos de suporte
support_src=src/include/visual.cpp \
            src/include/init.cpp

#compilar e executar
run:
	g++ $(src) $(geometry_src) $(support_src) -o $(exe) -std=$(cpp_v) $(include_paths) $(opengl_flags)
	./$(exe)

# Compilar e executar versão antiga (também usa a nova arquitetura)
old_run:
	g++ src/old_main.cpp $(geometry_src) $(support_src) -o $(exe) -std=$(cpp_v) $(include_paths) $(opengl_flags)
	./$(exe)

# only necessary in the beggining of the learning path
setup: 
	sudo apt update && sudo apt upgrade
	sudo apt install libglfw3-dev
	sudo apt install libgl1-mesa-dev libglu1-mesa-devfreeflut3-dev
	sudo apt install libglew-dev
	sudo apt install libglm-dev
# teve um erro de segmentation fault (core dumped) 
# por um tempo, e por eu estar usando o wsl, precisei fazer isso abaixo no terminal
# export MESA_LOADER_DRIVER_OVERRIDE=egl_swiftshader
# export LIBGL_ALWAYS_SOFTWARE=1

clean:
	rm $(exe)