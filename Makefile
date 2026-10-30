SRCS := srcs/init.c srcs/main.c srcs/parsing.c srcs/util.c srcs/time.c srcs/log.c srcs/clean.c srcs/thread.c srcs/coder.c srcs/monitor.c srcs/heap.c srcs/dongle.c

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

fclean: clean
	rm -f ${NAME}

re: fclean all

ARGS ?= 5 800 200 200 200 3 0 edf

norm:
	norminette srcs includes

valgrind: ${NAME}
	valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./${NAME} ${ARGS}

helgrind: ${NAME}
	valgrind --tool=helgrind --error-exitcode=1 ./${NAME} ${ARGS}

lint: norm valgrind helgrind

.PHONY: re fclean clean all norm valgrind helgrind lint