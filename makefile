compilar: main.cpp
	g++ main.cpp Line.cpp Vetor2.cpp Circle.cpp -w -lSDL2 -lSDL2_image -o exe
executar: exe
	./exe
