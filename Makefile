# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/03 15:11:30 by hahadiou          #+#    #+#              #
#    Updated: 2023/03/15 18:12:34 by hahadiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
FLAGS	= -Wall -Wextra -Werror -IINC

NAME	= pipex

INC	= inc
UTILS_PATH	= utils
SRC_PATH	= src
OBJ_PATH	= obj

SRCS = pipex.c \
		init.c \
		main.c \
		check.c
		
SRC		= $(addprefix $(SRC_PATH)/,$(SRCS))
OBJ		= $(addprefix $(OBJ_PATH)/,$(SRCS:.c=.o))

NOC		= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
WHITE	= \033[1;37m

all: $(NAME)

bonus: all

$(NAME): $(OBJ)
	@echo "$(YELLOW)Compiling Utils...$(NOC)"
	@make -sC $(UTILS_PATH)
	@echo "$(YELLOW)Compiling Pipex...$(NOC)"
	@$(CC) $(FLAGS) -L $(UTILS_PATH) -o $@ $^ -lft
	@echo "$(GREEN)$@$(NOC)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC)/$(NAME).h  $(INC)/$(UTILS_PATH).h 
	@mkdir -p obj
	@$(CC) $(FLAGS) -I$(INC) -c -o $@ $<
	
clean:
	@echo "$(RED)Deleting OBJS ✔️ $(NOC)"
	@make clean -sC $(UTILS_PATH)
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "$(RED)Deleting Binary ✔️$(NOC)"
	@make fclean -sC $(UTILS_PATH)
	@rm -f $(NAME) 

re: fclean all

.PHONY:	all bonus clean fclean re 
