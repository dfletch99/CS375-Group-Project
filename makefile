PROG = main

FLAGS = -Wall -Wextra -DDEBUG -g -std=c++14

all: $(PROG)   
$(PROG): $(PROG).o sort.h
	g++ $(FLAGS) $(PROG).o -o $(PROG)
$(PROG).o: $(PROG).cpp
	g++ $(FLAGS) -c $(PROG).cpp -o $(PROG).o

clean:
	rm -rf $(PROG)
	rm -rf *.o
run: all
	./$(PROG)

memcheck: all
	valgrind -v --leak-check=full ./$(PROG)
