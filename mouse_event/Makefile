NAME = mouse_event
FLAGS = -Wall -Wextra -Werror
S =		main.cpp 


SRC = $(addprefix srcs/,$(S))
OBJ= $(S:.cpp=.o)

all: $(NAME)

$(NAME): 
	g++  -c $(SRC) -I includes `pkg-config opencv --cflags`
	g++  $(OBJ) -o $(NAME) `pkg-config opencv --libs`

	

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) 

re: fclean $(NAME)


.PHONY: clean fclean re 
