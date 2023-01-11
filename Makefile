# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 11:14:53 by hahadiou          #+#    #+#              #
#    Updated: 2023/01/11 11:30:47 by hahadiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
FLAGS	= -Wall -Wextra -Werror

NAME	= pipex
NAMEB	= pipex_bonus

INC	= inc
LIBFT_PATH	= libft/
SRC_PATH	= src/
OBJ_PATH	= obj/
OBJB_PATH	= obj_bonus/

SRCS = pipex.c \
		process.c

SRCSB = pipex_bonus.c \
		process_bonus.c \
		heredoc.c
		
SRC		= $(addprefix $(SRC_PATH)/,$(SRCS))
SRC_B	= $(addprefix $(SRC_PATH)/,$(SRCSB))
OBJ		= $(addprefix $(OBJ_PATH)/,$(SRCS:.c=.o))
OBJB	= $(addprefix $(OBJB_PATH)/,$(SRCSB:.c=.o))

NOC		= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
WHITE	= \033[1;37m

all: $(NAME)

bonus: $(NAMEB)

$(NAME): $(OBJ)
	@echo "$(YELLOW)Compiling Libft...$(NOC)"
	@make -sC $(LIBFT_PATH)
	@echo "$(YELLOW)Compiling Pipex...$(NOC)"
	@$(CC) $(FLAGS) -L $(LIBFT_PATH) -o $@ $^ -lft
	@echo "$(GREEN)$@$(NOC)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC)/$(NAME).h
	@mkdir -p obj
	@$(CC) $(FLAGS) -I$(INC) -c -o $@ $<

$(NAMEB): $(OBJB)
	@echo "$(YELLOW)Compiling Libft...$(NOC)"
	@make -sC $(LIBFT_PATH)
	@echo "$(YELLOW)Compiling Pipex Bonus...$(NOC)"
	@$(CC) $(FLAGS) -L $(LIBFT_PATH) -o $@ $^ -lft
	@echo "$(GREEN)$@$(NOC)"

$(OBJB_PATH)/%.o: $(SRC_PATH)/%.c $(INC)/$(NAMEB).h
	@mkdir -p obj_bonus
	@$(CC) $(FLAGS) -I$(INC) -c -o $@ $<
	
clean:
	@echo "$(RED)clean$(NOC)"
	@make clean -sC $(LIBFT_PATH)
	@rm -rf $(OBJ_PATH)
	@rm -rf $(OBJB_PATH)

fclean: clean
	@echo "$(RED)fclean$(NOC)"
	@make fclean -sC $(LIBFT_PATH)
	@rm -f $(NAME) ${NAMEB}

re: fclean all


.PHONY:	all clean fclean re  