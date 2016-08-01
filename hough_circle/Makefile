

all:
	g++ -c hough_circle.cpp -Wall `pkg-config opencv --cppflags`
	g++ hough_circle.o -o hough_circle `pkg-config opencv --libs`

clean:
	rm -f hough_circle.o
fclean: clean
	rm -f hough_circle
