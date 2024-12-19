NAME	=	test

SRC		=	lib_tester.c

OBJS	=	${SRC:%.c=%.o}

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

INC_DIR	=	../

LIB		=	../libft.a

RM		=	rm -f

all:		${NAME}

${NAME}:	${LIB} ${OBJS}
			${CC} ${CFLAGS} $^ ${LIB} -o $@

%.o:		%.c
			echo hello
			$(CC) $(CFLAGS) -I$(INC_DIR) -c $^ -o $@

${LIB}:		
			make -C ${INC_DIR}

clean:
			${RM} ${OBJS}
			make -C ${INC_DIR} clean

fclean:		clean
			${RM} ${NAME}
			make -C ${INC_DIR} fclean

re:			fclean all

.PHONY:		all clean fclean re