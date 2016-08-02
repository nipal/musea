
NAME="folowing"

all:
	g++ -c $(NAME).cpp -Wall `pkg-config opencv --cflags`
	g++ $(NAME).o -o $(NAME) `pkg-config opencv --libs`

clean:
	rm -f $(NAME).o
fclean: clean
	rm -f $(NAME)
