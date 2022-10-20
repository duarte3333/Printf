SRCS	=  ft_printf.c \

OBJS	= ${SRCS:.c=.o}
INCS	= includes
NAME	= libftprintf.a
LIBC	= ar rc
LIBR	= ranlib
LIBFT   = Libft/libft.a
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror


.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${INCS}

${NAME}: libft.a ${OBJS}
	cp ${LIBFT} .
	mv libft.a ${NAME}
	${LIBC} ${NAME} ${OBJS}
	${LIBR} ${NAME}

all: ${NAME}

clean:
	${RM} ${OBJS}

libft.a:
	cd Libft && make all

lib_fclean:
	cd Libft && make fclean
fclean: clean lib_fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all, clean, fclean, re