NAME = btc
SRC = main.cpp BitcoinExchange.cpp
SRC_PATH = ./srcs/
OBJS = ${patsubst %.cpp, ${OBJS_PATH}/%.o, ${SRC}}
OBJS_PATH = ./objs/
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
INC = -I includes/

vpath %.cpp ${SRC_PATH}


all: ${NAME}

${OBJS}: ${OBJS_PATH}/%.o: %.cpp Makefile
	@mkdir -p ${OBJS_PATH}
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

${NAME}: ${OBJS}
	$(CC) $(CFLAGS) -o ${NAME} ${OBJS} $(INC)

clean:
	@rm -rf ${OBJS_PATH}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
