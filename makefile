
run: 
	g++ src/main.cpp src/include/*.cpp -o app -std=c++17 -lglfw -lGLEW -lGL
	./app

chat: 
#	apenas rodar
#	g++ main.cpp *.cpp -o programa -lglfw -lGLEW -lGL
# 	ver warnings úteis
#	g++ main.cpp *.cpp -Wall -Wextra -o programa -lglfw -lGLEW -lGL
#	mais limpo
#	g++ src/*.cpp main.cpp -Iinclude -lglfw -lGLEW -lGL -o programa

