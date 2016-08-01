

all:
	g++ -c hough_circle.cpp -Wall `pkg-config opencv --cppflags`
	g++ hough_circle.o -o hough_circle `pkg-config opencv --libs`

tmp:
	g++ -c tmp.cpp -Wall `pkg-config opencv --cppflags`
	g++ tmp.o -o tmp `pkg-config opencv --libs`
	
cam:
	g++ -c traking.cpp -Wall `pkg-config opencv --cppflags`
	g++ traking.o -o cam `pkg-config opencv --libs`
	

clean:
	rm -f hough_circle.o
	rm -f tmp.o
	rm -f traking.o
fclean: clean
	rm -f hough_circle
	rm -f cam
	rm -f tmp
