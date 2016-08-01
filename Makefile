

all:
	g++ -c helloworld.c -Wall `pkg-config opencv --cflags`
	g++ helloworld.o -o helloworld `pkg-config opencv --libs`

clean:
	rm -f helloworld.o
fclean: clean
	rm -f helloworld
