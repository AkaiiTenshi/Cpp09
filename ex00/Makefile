SRCS = main.cpp BitcoinExchange.cpp
SRCS_PATH = ./srcs/

OBJS = ${patsubst %.cpp, ${OBJS_PATH}/%.o, ${SRCS}}
OBJS_PATH = ./objs/

CC = c++
INC = -I includes/
CFLAGS = -Wall -Wextra -Werror -std=c++98

vpath %.cpp ${SRCS_PATH}

NAME = btc

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
