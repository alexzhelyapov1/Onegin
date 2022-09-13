all: Debug

clean:
	touch 1.o
	touch a.out
	rm *.o
	rm a.out

Debug: clean onegin.o main.o
	g++ -Wall -o a.out onegin.o main.o
	./a.out

onegin.o:
	g++ -Wall -c -o onegin.o onegin.cpp

main.o:
	g++ -Wall -c -o main.o main.cpp