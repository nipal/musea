.PHONY: clean fclean re 
NAME = folowing
FLAGS = -Wall -Wextra -Werror
S =		folowing.cpp\
		draw_ball_path.cpp\
		detection.cpp	

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


