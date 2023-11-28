NAME	=	test

SRC		=	lib_tester.c

OBJS	=	${SRC:%.c=%.o}

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

INC_DIR	=	~/Projects/Cursus/libft

LIB		=	libft.a

RM		=	rm -f

all:		${NAME}

${NAME}:	${LIB} ${OBJS}
			${CC} ${CFLAGS} $^ ${LIB} -o $@

${LIB}:		
			make -C ${INC_DIR}
			cp ${INC_DIR}/${LIB} .
			cp ${INC_DIR}/libft.h .
			make -C ${INC_DIR} fclean

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME} ${LIB} libft.h

re:			fclean all

.PHONY:		all clean fclean re