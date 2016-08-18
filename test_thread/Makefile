NAME = threading
FLAGS = -Wall -Wextra #-Werror
S =		test.cpp 


SRC = $(addprefix srcs/,$(S))
OBJ= $(S:.cpp=.o)

all: $(NAME)

$(NAME): 
	g++  $(SRC) $(FLAGS) -lpthread -I includes -o $(NAME)
#	g++  -D__LINUX_ALSA__ -D__LITTLE_ENDIAN -c $(FLAGS) $(SRC) -I /usr/include/stk -I includes `pkg-config opencv --cflags`
#	g++  $(OBJ) -o $(NAME) `pkg-config opencv --libs` -lstk -lpthread -lasound /usr/lib/x86_64-linux-gnu/librtaudio.so.4v5

	

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) 

re: fclean $(NAME)


.PHONY: clean fclean re 
