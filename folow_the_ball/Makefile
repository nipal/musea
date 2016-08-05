NAME = folowing
FLAGS = -Wall -Wextra -Werror
S =		folowing.cpp \
		draw_ball_path.cpp \
		detection_v2.cpp 	


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
