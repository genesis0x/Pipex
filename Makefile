NAME        = pipex
CC        = gcc
FLAGS    = -Wall -Wextra -Werror

SRCS        =     		process.c \
                        	pipex.c \
							libft/ft_memcpy.c \
							libft/ft_split.c \
							libft/ft_strchr.c \
							libft/ft_strdup.c \
							libft/ft_strjoin.c \
							libft/ft_strlen.c \
							libft/ft_strncmp.c \
							libft/ft_strnstr.c \
							libft/ft_strrchr.c \
							libft/ft_substr.c \
							libft/get_next_line.c \
							libft/ft_dprintf.c


SRCS_BONUS	=			process_bonus.c \
							pipex_bonus.c \
							heredoc.c \
							libft/ft_memcpy.c \
							libft/ft_split.c \
							libft/ft_strchr.c \
							libft/ft_strdup.c \
							libft/ft_strjoin.c \
							libft/ft_strlen.c \
							libft/ft_strncmp.c \
							libft/ft_strnstr.c \
							libft/ft_strrchr.c \
							libft/ft_substr.c \
							libft/get_next_line.c \
							libft/ft_dprintf.c

CLR_RMV		= \033[0m
RED		    = \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
CYAN 		= \033[1;36m

OBJS        = $(SRCS:.c=.o)

OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}


RM		    = rm -f

all:		${NAME}

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@${CC} ${FLAGS} -o ${NAME} ${OBJS} 
			@echo "$(GREEN)$(NAME) created[0m ✔️"

bonus	:	${OBJS_BONUS}
			@echo "$(GREEN)Compilation ${CLR_RMV}Bonus of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@${CC} ${FLAGS} -o ${NAME} ${OBJS_BONUS} 
			@echo "$(GREEN)$(NAME) created[0m ✔️"

clean:	
			@ ${RM} ${OBJS} ${OBJS_BONUS}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)OBJS ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)${NAME} ✔️"

re:			fclean all

.PHONY:		all clean fclean re
