NAME	=	test

SRC		=	lib_tester.c

OBJS	=	${SRC:%.c=%.o}

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

LIBFT_DIR	= ../../libft
LIBFT_INC	= ${LIBFT_DIR}/inc#add path here if libft.h is not in the root

LIB		=	${LIBFT_DIR}/libft.a

RM		=	rm -f

all:		${NAME}

${NAME}:	${LIB} ${OBJS}
			${CC} ${CFLAGS} $^ ${LIB} -o $@

%.o:		%.c
			${CC} ${CFLAGS} -I${LIBFT_INC} -c $< -o $@

${LIB}:		
			make -C ${LIBFT_DIR}

clean:
			${RM} ${OBJS}
			make -C ${LIBFT_DIR} clean

fclean:		clean
			${RM} ${NAME}
			make -C ${LIBFT_DIR} fclean

re:			fclean all

.PHONY:		all clean fclean re
