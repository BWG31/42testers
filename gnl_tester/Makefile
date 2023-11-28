NAME	=	test

TEST_SRC	= gnl_tester.c

SRC_GNL	=	get_next_line.c \
			get_next_line_utils.c \

OBJ_GNL =	${SRC_GNL:%.c=%.o} ${TEST_SRC:%.c=%.o}

HDR_SRC_GNL	=	get_next_line.h

LIB		= get_next_line.a

CC		=	cc

CFLAGS	=	-Wall -Werror -Wextra

GNL_DIR	=	~/Projects/Cursus/get_next_line

RM		=	rm -rf

all:		${NAME}

${NAME}:	${HDR_SRC_GNL} ${OBJ_GNL} ${LIB}
			${CC} ${CFLAGS} ${OBJ_GNL} -o $@

${LIB}:		${HDR_SRC_GNL} ${OBJ_GNL}
			-ar -rc $@ $^

%.o:		%.c ${HDR_SRC_GNL}
			${CC} ${CFLAGS} -c $< -o $@

${SRC_GNL}:
			cp ${GNL_DIR}/get_next_line.c .
			cp ${GNL_DIR}/get_next_line_utils.c .

${HDR_SRC_GNL}:
			cp ${GNL_DIR}/${HDR_SRC_GNL} .

clean:
			${RM} ${OBJ_GNL}

fclean:		clean
			${RM} ${NAME} ${HDR_SRC_GNL} ${SRC_GNL} ${LIB}
			${RM} debug

re:			fclean all

.PHONY:		all clean fclean re