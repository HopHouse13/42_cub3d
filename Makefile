# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 17:10:30 by pbret             #+#    #+#              #
#    Updated: 2025/09/10 13:35:08 by tjacquel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
SRCS_DIR	= sources
OBJ_DIR 	= obj_$(NAME)
SRCS		= sources/main.c \
			sources/parsing.c

OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)
CC			= cc
RM			= rm -rf
CFLAGS		= -Wall -Werror -Wextra -ggdb -I./includes

# Headers & libraries
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFTH = -I $(LIBFT_DIR)

$(OBJ_DIR)/%.o : $(SRCS_DIR)/%.c
			@mkdir -p $(@D)
			@$(CC) -g $(CFLAGS) $(LIBFTH) -c $< -o $@

all:		$(NAME)

$(LIBFT):
			@make -C $(LIBFT_DIR)

$(NAME):	$(LIBFT) $(OBJS)
			@$(CC) $(OBJS) $(LIBFT) -o $(NAME) -g
			@echo "\033[32m""Compilation of $(NAME) completed!""\033[0m"

clean:
			@$(RM) $(OBJ_DIR)
			@make -C $(LIBFT_DIR) clean
			@echo "\033[36m""Directory $(OBJ_DIR) deleted.""\033[0m"

fclean:		clean
			@$(RM) $(NAME)
			@make -C $(LIBFT_DIR) fclean
			@echo "\033[36m""Executable $(NAME) deleted.""\033[0m"

re:			fclean 	all

.PHONY: all clean fclean re