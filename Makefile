# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 17:10:30 by pbret             #+#    #+#              #
#    Updated: 2025/10/23 00:53:36 by tjacquel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ============================================================================ #
#                                   NAMES                                      #
# ============================================================================ #

NAME		= cub3D
NAME_BONUS	= cub3D_bonus

# ============================================================================ #
#                                DIRECTORIES                                   #
# ============================================================================ #

SRCS_DIR		= sources/
SRCS_BONUS_DIR	= sources_bonus/
OBJ_DIR			= obj_$(NAME)
OBJ_BONUS_DIR	= obj_$(NAME_BONUS)

LIBFT_DIR	= ./lib/libft
LIBFT		= $(LIBFT_DIR)/libft.a

MLX_DIR	= ./minilibx-linux
MLX_LIB	= $(MLX_DIR)/libmlx.a

# ============================================================================ #
#                              MANDATORY SOURCES                               #
# ============================================================================ #

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

SRCS_EXEC = \
	exec/ray_game_mechanics.c \
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
SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS		= $(SRCS:$(SRCS_DIR)%.c=$(OBJ_DIR)/%.o)

# ============================================================================ #
#                               BONUS SOURCES                                  #
# ============================================================================ #

SRCS_BONUS_PARSING = \
	parsing_bonus/check_colors_bonus.c\
	parsing_bonus/check_elem_bonus.c \
	parsing_bonus/check_filename_bonus.c \
	parsing_bonus/check_map_1_bonus.c \
	parsing_bonus/check_map_bonus.c \
	parsing_bonus/check_paths_bonus.c \
	parsing_bonus/copy_map_bonus.c \
	parsing_bonus/init_parsing_bonus.c \
	parsing_bonus/parsing_bonus.c

SRCS_BONUS_UTILS = \
	utilities_bonus/get_next_line_utilities_bonus.c \
	utilities_bonus/get_next_line_bonus.c \
	utilities_bonus/handle_exit_bonus.c \
	utilities_bonus/print_debug_bonus.c \
	utilities_bonus/print_ray_debug_bonus.c \

SRCS_BONUS_EXEC = \
	exec_bonus/ray_game_mechanics_bonus.c \
	exec_bonus/ray_game_mechanics2_bonus.c \
	exec_bonus/ray_init_stuff_bonus.c \
	exec_bonus/ray_init_stuff2_bonus.c \
	exec_bonus/ray_mlx_stuff_bonus.c \
	exec_bonus/ray_render_stuff_bonus.c \
	exec_bonus/ray_render_utils_bonus.c \
	exec_bonus/ray_utils_bonus.c \
	exec_bonus/raycaster_bonus.c \
	exec_bonus/ray_txtr_render_bonus.c \
	exec_bonus/mouse_mvmt_bonus.c \
	exec_bonus/minimap_render_2drays_bonus.c \
	exec_bonus/minimap_render_scaled_bonus.c \
	exec_bonus/minimap_render_viewport_bonus.c \
	exec_bonus/exec_launch_bonus.c \
	exec_bonus/doors_bonus.c \
	exec_bonus/doors_helper_bonus.c \
	exec_bonus/fog_bonus.c \
	exec_bonus/animated_sprite_bonus.c \
	exec_bonus/animated_sprite_init_bonus.c \
	exec_bonus/animated_sprite_render_bonus.c \
	exec_bonus/helper_bonus.c \

SRCS_BONUS_FILES	= main_bonus.c $(SRCS_BONUS_PARSING) $(SRCS_BONUS_EXEC) $(SRCS_BONUS_UTILS)
SRCS_BONUS			= $(addprefix $(SRCS_BONUS_DIR), $(SRCS_BONUS_FILES))
OBJS_BONUS			= $(SRCS_BONUS:$(SRCS_BONUS_DIR)%.c=$(OBJ_BONUS_DIR)/%.o)

# ============================================================================ #
#                              COMPILATION FLAGS                               #
# ============================================================================ #

CC			= cc
RM			= rm -rf
CFLAGS		= -Wall -Werror -Wextra
INCLUDES	= -I./includes -I$(LIBFT_DIR) -I$(MLX_DIR)
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lXfixes

# ============================================================================ #
#                                   RULES                                      #
# ============================================================================ #

all: $(NAME)

bonus: $(NAME_BONUS)

# ============================================================================ #
#                            MANDATORY COMPILATION                             #
# ============================================================================ #

$(OBJ_DIR)/%.o: $(SRCS_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) -g $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME) -g
	@echo "\033[32mCompilation of $(NAME) completed!\033[0m"

# ============================================================================ #
#                             BONUS COMPILATION                                #
# ============================================================================ #

$(OBJ_BONUS_DIR)/%.o: $(SRCS_BONUS_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) -g $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME_BONUS): $(LIBFT) $(MLX_LIB) $(OBJS_BONUS)
	@$(CC) $(OBJS_BONUS) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME_BONUS) -g
	@echo "\033[35mCompilation of $(NAME_BONUS) completed!\033[0m"

# ============================================================================ #
#                            LIBRARY COMPILATION                               #
# ============================================================================ #

$(LIBFT):
	@make -sC $(LIBFT_DIR)

$(MLX_LIB):
	@make -sC $(MLX_DIR)

# ============================================================================ #
#                               CLEAN RULES                                    #
# ============================================================================ #

clean:
	@$(RM) $(OBJ_DIR) $(OBJ_BONUS_DIR)
	@echo "\033[36mDirectories $(OBJ_DIR) and $(OBJ_BONUS_DIR) deleted.\033[0m"
	@make -sC $(LIBFT_DIR) clean
	@make -sC $(MLX_DIR) clean

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS)
	@echo "\033[36mExecutables $(NAME) and $(NAME_BONUS) deleted.\033[0m"
	@make -sC $(LIBFT_DIR) fclean

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus
