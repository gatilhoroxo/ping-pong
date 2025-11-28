src=src/main.cpp
exe=app

cpp_v=c++17

opengl_flags=-lglfw -lGLEW -lGL

#compilar e executar
run:
	g++ $(src) -o $(exe) -std=$(cpp_v) $(opengl_flags)
	./$(exe)

# only necessary in the beggining of the learning path
setup: 
	sudo apt update && sudo apt upgrade
	sudo apt install libglfw3-dev
	sudo apt install libgl1-mesa-dev libglu1-mesa-devfreeflut3-dev
	sudo apt install libglew-dev
# teve um erro de segmentation fault (core dumped) 
# por um tempo e por eu estar usando o wsl preciso fazer isso abaixo no terminal
# export MESA_LOADER_DRIVER_OVERRIDE=egl_swiftshader
# export LIBGL_ALWAYS_SOFTWARE=1

clean:
