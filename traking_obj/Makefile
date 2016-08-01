

all:
	g++ -c traking.cpp -Wall `pkg-config opencv --cflags`
	g++ traking.o -o traking `pkg-config opencv --libs`

clean:
	rm -f traking.o
fclean: clean
	rm -f traking
