exe=app
cpp_v=c++17

local_libs_flags=-Iinclude -I$(HOME)/.local/storage/lib_opengl/include \
					-L$(HOME)/.local/storage/lib_opengl/lib \
					-lGLEW -lglfw3 -lGL -lGLU -lpthread -ldl


teste:
	g++ src/teste.cpp -o $(exe) \
		-std=$(cpp_v) $(local_libs_flags) 
		