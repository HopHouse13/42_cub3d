# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbret <pbret@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 17:10:30 by pbret             #+#    #+#              #
#    Updated: 2025/10/22 22:07:02 by pbret            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME		= cub3D
SRCS_DIR	= sources/
OBJ_DIR 	= obj_$(NAME)

SRCS_PARSING = \
	parsing/check_colors.c\
	parsing/check_elem.c \
	parsing/check_filename.c \
	parsing/check_map_1.c \
	parsing/check_map.c \
	parsing/check_paths.c \
	parsing/copy_map.c \
	parsing/init_parsing.c \
	parsing/parsing.c

SRC_UTILS = \
	utilities/get_next_line_utilities.c \
	utilities/get_next_line.c \
	utilities/handle_exit.c \
	utilities/print_debug.c \
	utilities/print_ray_debug.c \

SRCS_EXEC = exec/ray_game_mechanics.c \
	exec/ray_game_mechanics2.c \
	exec/ray_init_stuff.c \
	exec/ray_init_stuff2.c \
	exec/ray_mlx_stuff.c \
	exec/ray_render_stuff.c \
	exec/ray_render_utils.c \
	exec/ray_utils.c \
	exec/raycaster.c \
	exec/ray_txtr_render.c \
	exec/mouse_mvmt_bonus.c \
	exec/minimap_render_2drays_bonus.c \
	exec/minimap_render_scaled_bonus.c \
	exec/minimap_render_viewport_bonus.c \
	exec/exec_launch.c \
	exec/doors_bonus.c \
	exec/doors_helper_bonus.c \
	exec/fog_bonus.c \
	exec/animated_sprite_bonus.c \
	exec/animated_sprite_init_bonus.c \
	exec/animated_sprite_render_bonus.c \
	exec/helper_bonus.c \



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
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lXfixes

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
			@echo "\033[36m""Directory $(OBJ_DIR) deleted.""\033[0m"
			@make -sC $(LIBFT_DIR) clean
			@make -sC $(MLX_DIR) clean
			@echo "\033[36m""Directory $(OBJ_DIR) deleted.""\033[0m"
			@make -sC $(LIBFT_DIR) clean
			@make -sC $(MLX_DIR) clean

fclean:		clean
			@$(RM) $(NAME)
			@echo "\033[36m""Executable $(NAME) deleted.""\033[0m"
			@make -sC $(LIBFT_DIR) fclean
			@echo "\033[36m""Executable $(NAME) deleted.""\033[0m"
			@make -sC $(LIBFT_DIR) fclean

re:			fclean 	all

.PHONY: all clean fclean re