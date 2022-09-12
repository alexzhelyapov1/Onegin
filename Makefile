all: Debug

clean:
	touch 1.o
	rm *.o

Debug: clean onegin.o main.o
	g++ -Wall -o a.out onegin.o main.o
	./a.out

onegin.o:
	g++ -Wall -c -o onegin.o onegin.cpp

main.o:
	g++ -Wall -c -o main.o main.cpp