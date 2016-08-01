# compilation
g++ -c helloworld.c -Wall `pkg-config opencv --cflags`

# édition des liens
g++ helloworld.o -o helloworld `pkg-config opencv --libs`
