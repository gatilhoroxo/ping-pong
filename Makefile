src=src/main.cpp
exe=app

cpp_v=c++17
opengl_flags=-lglfw -lGLEW -lGL 
include_paths=-I/usr/include -Iinclude

# Arquivos da arquitetura de formas geométricas
geometry_src=include/geometry/Forma.cpp \
             include/geometry/Triangulo.cpp \
             include/geometry/Quadrado.cpp \
             include/geometry/Retangulo.cpp \
             include/geometry/Circulo.cpp

# Arquivos de suporte
support_src=include/visual.cpp \
            include/init.cpp

#compilar e executar
run:
	g++ $(src) $(geometry_src) $(support_src) -o $(exe) \
		-std=$(cpp_v) $(include_paths) $(opengl_flags)
	./$(exe)

# only necessary in the beggining of the learning path
setup: 
	sudo apt update && sudo apt upgrade
	sudo apt install -y libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev libglew-dev libglm-dev
# teve um erro de segmentation fault (core dumped) 
# por um tempo, e por eu estar usando o wsl, precisei fazer isso abaixo no terminal
# export MESA_LOADER_DRIVER_OVERRIDE=egl_swiftshader
# export LIBGL_ALWAYS_SOFTWARE=1

clean:
	rm $(exe)
