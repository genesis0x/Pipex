SRCS =	ft_dprintf.c \
		ft_memcpy.c \
		ft_split.c \
		ft_strchr.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_substr.c \
		get_next_line.c

OBJS = ${SRCS:.c=.o}

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: ${NAME}

.c.o:
			@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
			@ar -rc $(NAME) $(OBJS)

clean:
			@${RM} ${OBJS}

fclean: clean
			@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
