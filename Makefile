# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbret <pbret@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 17:10:30 by pbret             #+#    #+#              #
#    Updated: 2025/09/11 17:22:37 by pbret            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
SRCS_DIR	= sources/
OBJ_DIR 	= obj_$(NAME)

SRCS_PARSING = \
	parsing/parsing.c \
	parsing/check_filename.c \
	parsing/check_elem.c \

SRC_UTILS = \
	utilities/init_data.c

# SRCS_EXEC = exec/

SRCS_FILES	= main.c $(SRCS_PARSING) $(SRCS_EXEC) $(SRC_UTILS)

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))


OBJS		= $(SRCS:$(SRCS_DIR)%.c=$(OBJ_DIR)/%.o)
CC			= cc
RM			= rm -rf
CFLAGS		= -Wall -Werror -Wextra

LIBFT_DIR = ./lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

GNL_DIR = ./lib/get_next_line
GNL = $(GNL_DIR)/get_next_line.a

INCLUDES = -I./includes -I$(LIBFT_DIR) -I$(GNL_DIR)


# Pattern rule for object files
$(OBJ_DIR)/%.o : $(SRCS_DIR)%.c
			@mkdir -p $(@D)
			@$(CC) -g $(CFLAGS) $(INCLUDES) -c $< -o $@


all:		$(NAME)

$(LIBFT):
			@make -sC $(LIBFT_DIR)

$(GNL):
			@make -sC $(GNL_DIR) > /dev/null

$(NAME):	$(LIBFT) $(GNL) $(OBJS)
			@ $(CC) $(OBJS) $(LIBFT) $(GNL) -o $(NAME) -g
			@echo "\033[32m""Compilation of $(NAME) completed!""\033[0m"

clean:
			@$(RM) $(OBJ_DIR)
			@make -sC $(LIBFT_DIR) clean
			@make -sC $(GNL_DIR) clean
			@echo "\033[36m""Directory $(OBJ_DIR) deleted.""\033[0m"

fclean:		clean
			@$(RM) $(NAME)
			@make -sC $(LIBFT_DIR) fclean
			@make -sC $(GNL_DIR) fclean
			@echo "\033[36m""Executable $(NAME) deleted.""\033[0m"

re:			fclean 	all

.PHONY: all clean fclean re