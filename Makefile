# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: femaury <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/18 20:03:09 by femaury           #+#    #+#              #
#    Updated: 2018/06/23 13:32:23 by femaury          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SRC_PATH = srcs
SRC_NAME = fdf_main.c
OBJ_PATH = objs
OBJ_NAME = $(SRC_NAME:.c=.o)
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -framework OpenGL -framework AppKit

.PHONY: all, clean, fclean, re

all:
	@$(MAKE) -C libft/
	@$(MAKE) -C minilibx/
	@echo ""
	@$(MAKE) $(NAME)

$(NAME): $(OBJ) libft/libft.a
	@$(CC) $(CFLAGS) -Iincs -o $(NAME) $(OBJ) libft/libft.a libft/ft_printf/libftprintf.a minilibx/libmlx.a $(MLXFLAGS)
	@echo "\n[\033[32mOK\033[0m] $(NAME) compiled successfully."

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -Iincs -o $@ -c $<
	@echo "[\033[32mOK\033[0m] $@ compiled successfully."

clean:
ifeq ($(MAKECMDGOALS), clean)
	@$(RM) $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@$(MAKE) -C libft/ clean
	@$(MAKE) -C minilibx/ clean
	@echo "\n[\033[32mOK\033[0m] minilibx cleaned.\n"
	@echo "\n[\033[32mOK\033[0m] $(NAME) objects cleaned.\n"
else
	@$(RM) $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "\n[\033[32mOK\033[0m] $(NAME) objects cleaned.\n"
endif

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft/ fclean
	@$(MAKE) -C minilibx/ clean
	@echo "\n[\033[32mOK\033[0m] minilibx cleaned.\n"
	@echo "\n[\033[32mOK\033[0m] $(NAME) \033[31mhas been removed.\033[0m\n"

re: fclean all
