ex1: ex1.cpp Vector.o
	@g++ ex1.cpp Vector.o -lGL -lglut -o ex1
ex2: ex2.cpp Vector.o
	@g++ -oex2 ex2.cpp -lGL -lglut -lGLU
run-ex1: ex1
	./ex1
run-ex2: ex2
	./ex2
Vector.o: Vector.h Vector.cpp
	@g++ -c Vector.cpp -o Vector.o
