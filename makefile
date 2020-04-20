PROG1 = AviFileName
PROG2 = DavidFileName
PROG3 = quicksort
PROG4 = quicksortRandom

FLAGS = -Wall -Wextra -DDEBUG -g -std=c++14

all: $(PROG1) $(PROG2) $(PROG3) $(PROG4)
$(PROG1): $(PROG1).o
	g++ $(FLAGS) $(PROG1).o -o $(PROG1)
$(PROG1).o: $(PROG1).cpp
	g++ $(FLAGS) -c $(PROG1).cpp -o $(PROG1).o
$(PROG2): $(PROG2).o
	g++ $(FLAGS) $(PROG2).o -o $(PROG2)
$(PROG2).o: $(PROG2).cpp
	g++ $(FLAGS) -c $(PROG2).cpp -o $(PROG2).o
$(PROG3): $(PROG3).o
	g++ $(FLAGS) $(PROG3).o -o $(PROG3)
$(PROG3).o: $(PROG3).cpp
	g++ $(FLAGS) -c $(PROG3).cpp -o $(PROG3).o
$(PROG4): $(PROG4).o
	g++ $(FLAGS) $(PROG4).o -o $(PROG4)
$(PROG4).o: $(PROG4).cpp
	g++ $(FLAGS) -c $(PROG4).cpp -o $(PROG4).o
clean:
	rm -rf $(PROG1)
	rm -rf $(PROG2)
	rm -rf $(PROG3)
	rm -rf $(PROG4)
	rm -rf *.o
run: all
	./$(PROG1) input.txt output.txt
	./$(PROG2) input.txt output.txt
	./$(PROG3) input.txt output.txt
	./$(PROG4) input.txt output.txt
run1: $(PROG1)
	./$(PROG1) input.txt output.txt
run2: $(PROG2)
	./$(PROG2) input.txt output.txt
run3: $(PROG3)
	./$(PROG3) input.txt output.txt
run4: $(PROG4)
	./$(PROG4) input.txt output.txt
memcheck: all
	valgrind -v --leak-check=full ./$(PROG1)
