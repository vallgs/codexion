SRCS := int.c main.c parsing.c util.c 

includes := codex.h

SRC_OBJS := $(SRCS:.c=.o)
CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread
NAME := codexion

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${SRC_OBJS}
	ar rcs ${NAME} ${SRC_OBJS}

all: ${NAME}

clean:
	rm -f ${SRC_OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: re fclean clean all