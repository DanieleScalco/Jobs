
main.exe: main.o
	g++ -std=c++0x -O3 -DNDEBUG main.o -o main.exe

main.o: main.cpp multiset.h
	g++ -c main.cpp -o main.o



.PHONY: clean

clean:
	rm *.exe *.o