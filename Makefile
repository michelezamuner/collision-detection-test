.PHONY: run
OBJECTS = ex1.o Vector.o

ex1: $(OBJECTS)
	@g++ $(OBJECTS) -l GL -lglut -o ex1

run: ex1
	./ex1

ex1.o: ex1.cpp include/slc/Vector.h
	@g++ -I./include -c ex1.cpp -o ex1.o

Vector.o: src/slc/Vector.cpp include/slc/Vector.h
	@g++ -I./include -c src/slc/Vector.cpp -o Vector.o

