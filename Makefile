# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbret <pbret@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 17:10:30 by pbret             #+#    #+#              #
#    Updated: 2025/10/02 18:31:31 by pbret            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= cub3D
SRCS_DIR	= sources/
OBJ_DIR 	= obj_$(NAME)

SRCS_PARSING = \
	parsing/check_filename.c \
	parsing/check_elem.c \
	parsing/parsing.c \
	parsing/check_map.c \
	parsing/copy_map.c

SRC_UTILS = \
	utilities/handle_exit.c \
	utilities/init_data.c \
	utilities/get_next_line.c \
	utilities/get_next_line_utilities.c \
	utilities/print_debug.c

SRCS_EXEC = exec/ray_game_mechanics.c \
	exec/ray_init_stuff.c \
	exec/ray_mlx_stuff.c \
	exec/ray_render_stuff.c \
	exec/ray_render_utils.c \
	exec/ray_utils.c \
	exec/raycaster.c \


SRCS_FILES	= main.c $(SRCS_PARSING) $(SRCS_EXEC) $(SRC_UTILS)

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS		= $(SRCS:$(SRCS_DIR)%.c=$(OBJ_DIR)/%.o)
CC			= cc
RM			= rm -rf
CFLAGS		= -Wall -Werror -Wextra

LIBFT_DIR = ./lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I./includes -I$(LIBFT_DIR) -I$(MLX_DIR)

# MinilibX settings
MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm


# Pattern rule for object files
$(OBJ_DIR)/%.o : $(SRCS_DIR)%.c
			@mkdir -p $(@D)
			@$(CC) -g $(CFLAGS) $(INCLUDES) -c $< -o $@


all:		$(NAME)

$(LIBFT):
			@make -sC $(LIBFT_DIR)

$(MLX_LIB):
			@make -sC $(MLX_DIR)
			
$(NAME):	$(LIBFT) $(MLX_LIB) $(OBJS)
			@ $(CC) $(OBJS) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME) -g
			@echo "\033[32m""Compilation of $(NAME) completed!""\033[0m"

clean:
			@$(RM) $(OBJ_DIR)
			@make -sC $(LIBFT_DIR) clean
			@echo "\033[36m""Directory $(OBJ_DIR) deleted.""\033[0m"

fclean:		clean
			@$(RM) $(NAME)
			@make -sC $(LIBFT_DIR) fclean
			@rm $(MLX_LIB)
			@rm $(MLX_DIR)/libmlx_Linux.a
			@echo "\033[36m""Executable $(NAME) deleted.""\033[0m"

re:			fclean 	all

.PHONY: all clean fclean re