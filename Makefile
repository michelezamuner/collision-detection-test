.PHONY: run clean
OBJECTS = ex1.o Vector.o
EXECUTABLES = ex1 ex2

ex1: $(OBJECTS)
	@g++ $(OBJECTS) -lGL -lglut -o ex1

run: ex1
	./ex1

clean:
	@find . -name "*.o" -exec rm {} \;
	@rm -f $(EXECUTABLES)

ex1.o: ex1.cpp include/slc/Vector.h
	@g++ -I./include -c ex1.cpp -o ex1.o

Vector.o: src/slc/Vector.cpp include/slc/Vector.h
	@g++ -I./include -c src/slc/Vector.cpp -o Vector.o

