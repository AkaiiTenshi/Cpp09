NAME = RPN
SRC = main.cpp RPN.cpp
SRC_DIR = ./src/
OBJ = ${patsubst %.cpp, $(OBJ_DIR)%.o, $(SRC)}
OBJ_DIR = ./obj/
CC = c++ 
CFLAGS = -Wall -Werror -Wextra -g3 -std=c++98
INC = -I ./include/

vpath %.cpp $(SRC_DIR)

all: $(NAME)

$(OBJ): $(OBJ_DIR)%.o: %.cpp Makefile
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME)

clean: 
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean

