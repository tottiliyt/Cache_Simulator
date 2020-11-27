CC = g++
CFLAGS = -std=c++11 -Wextra -Wall -pedantic
DBGFLAGS = -g

csim: cache_main.o cache_simulator.o
	$(CC) $(CFLAGS) $(DBGFLAGS) cache_simulator.o cache_main.o -o csim 

cache_main.o: cache_main.cpp
	$(CC) $(CFLAGS) $(DBGFLAGS) -c cache_main.cpp -o cache_main.o 

cache_simulator.o: cache_simulator.cpp cache_simulator.h
	$(CC) $(CFLAGS) $(DBGFLAGS) -c cache_simulator.cpp -o cache_simulator.o

clean:
	rm -f *.o cache_simulator 

