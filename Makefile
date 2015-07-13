ex1: ex1.cpp
	g++ -oex1 ex1.cpp -lGL -lglut
ex2: ex2.cpp
	g++ -oex2 ex2.cpp -lGL -lglut -lGLU
run-ex1: ex1
	./ex1
run-ex2: ex2
	./ex2
