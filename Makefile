
output: main.o
	g++ -o output main.o -lpthread -lrt

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f *.o output