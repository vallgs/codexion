SRCS := srcs/init.c srcs/main.c srcs/parsing.c srcs/util.c srcs/time.c srcs/log.c srcs/clean.c

includes := includes/codex.h

SRC_OBJS := $(SRCS:.c=.o)
CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread -Iincludes
NAME := codexion

all: ${NAME}

%.o: %.c ${includes}
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${SRC_OBJS}
	${CC} -o ${NAME} ${SRC_OBJS} ${CFLAGS}

clean:
	rm -f ${SRC_OBJS}
	rm -f

fclean: clean
	rm -f ${NAME}
	rm -f a.out

re: fclean all

.PHONY: re fclean clean all