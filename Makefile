
output: main.o
	g++ -main.o -o output -lcurl

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f *.o output