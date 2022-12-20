NAME        := pipex
CC        := gcc
FLAGS    := -Wall -Wextra -Werror

SRCS        :=     		process.c \
                        libft/ft_split.c \
                        libft/ft_strchr.c \
                        libft/ft_strjoin.c \
                        libft/ft_strlen.c \
                        libft/ft_strncmp.c \
                        libft/ft_substr.c \
						libft/ft_strrchr.c \
						libft/ft_memmove.c \
						libft/ft_memcpy.c \
						libft/ft_strdup.c \
						libft/ft_strlcat.c \
						libft/ft_strtrim.c \
						libft/ft_strnstr.c \
						dprintf/ft_dprintf.c \
                        pipex.c

SRCS_B        :=     	process_bonux.c \
                        libft/ft_split.c \
                        libft/ft_strchr.c \
                        libft/ft_strjoin.c \
                        libft/ft_strlen.c \
                        libft/ft_strncmp.c \
                        libft/ft_substr.c \
						libft/ft_strrchr.c \
						libft/ft_memmove.c \
						libft/ft_memcpy.c \
						libft/ft_strdup.c \
						libft/ft_strlcat.c \
						libft/ft_strtrim.c \
						libft/ft_strnstr.c \
						dprintf/ft_dprintf.c \
                        pipex_bonux.c

OBJS        := $(SRCS:.c=.o)
OBJS_B        := $(SRCS_B:.c=.o)

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@${CC} ${{FLAGS} -o ${NAME} ${OBJS}
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		${OBJS_B}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@${CC} ${{FLAGS} -o ${NAME} ${OBJS_B}
			@echo "$(GREEN)$(NAME) created[0m ✔️"

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)OBJS ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)Binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re
