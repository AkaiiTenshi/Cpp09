NAME: btc
SRC: main.cpp BitcoinExchange.cpp
CC: c++
CFLAGS: -Wall -Werror -Wextra -std=c++98 -g3
OBJ:$(SRC:.cpp=.o)

all: $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) $(SRC) -c $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean: 
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean

