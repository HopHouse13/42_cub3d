/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:28:01 by pbret             #+#    #+#             */
/*   Updated: 2025/10/23 01:34:47 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ========================================================================== */
/*                                  LIBRARIES                                 */
/* ========================================================================== */

# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "mlx.h"
# include "../lib/libft/libft.h"
# include "error.h"
# include "macros.h"
# include "structs.h"

/* ========================================================================== */
/*                             PARSING_FUNCTIONS                              */
/* ========================================================================== */

/// PARSING ///
void		parsing(t_cub *cub, char *argv);
void		init_parsing_data(t_cub *cub);

// PARSING_CHECK_FILENAME ///
void		check_filename(t_cub *cub, char *argv);

// PARSING_CHECK_ELEM //
void		check_elem(t_cub *cub, char *file_map);
void		handle_paths(t_cub *cub, char **line, t_key key_id);
void		handle_colors(t_cub *cub, char **line, t_key key_id);

// PARSING_CHECK_MAP ///
void		make_copy(t_cub *cub, char *mapfile);
void		check_map(t_cub *cub, char *mapfile);
void		empty_line(t_cub *cub);

/// UTILITIES ///
void		exit_door(t_cub *cub, char *err_id, char *item);

/// PARSING_UTILITIES ///
char		*get_next_line(int fd, char **err_id, bool exit_door);
char		*gnl_strdup(const char *s, char **err_id);
char		*gnl_strjoin(const char *s1, const char *s2, char **err_id);

/* ========================================================================== */
/*                                EXEC_FUNCTIONS                              */
/* ========================================================================== */

// init_stuff
void		exec_launch(t_cub *cub);
void		init_textures(t_cub *cub);
void		init_exec_data(t_cub *cub);
void		init_player(t_cub *cub, t_player *player);
void		init_image(t_cub *cub);
void		init_ray_data(t_ray *ray);
void		init_player_time(t_cub *cub, t_player *player);

// mlx_stuff
void		cleanup_mlx(t_cub *cub, char *mlx_err, char *item);

// render_stuff
void		render_cubes(t_cub *cub, t_player *player, t_ray *ray, int x);
void		raycasting_loop(t_cub *cub, t_player *player, t_ray *ray);
void		render(t_cub *cub);

// game_stuff
int			key_press_hook(int keysym, t_cub *cub);
int			key_release_hook(int keysym, t_cub *cub);
void		handle_move(t_cub *cub, t_player *player);
void		turn_right(t_cub *cub, t_player *player);
void		turn_left(t_cub *cub, t_player *player);
bool		is_valid_move(t_cub *cub, double x, double y);

// utils
uint32_t	char_to_tile_rgb(char c);
double		date_in_s(t_cub *cub);
double		date_in_ms(t_cub *cub);
void		print_txtr_struct(t_txtr *txtr);

// render utils
void		img_pxl_put(t_img *img, int x, int y, int color);
int			render_empty_sqr(t_img *img, t_sqr sqr);
int			render_outlined_sqr(t_img *img, t_sqr sqr);
int			render_rect(t_img *img, t_rect rect);

// render textures
void		render_texture(t_cub *cub, t_ray *ray, t_txtr *txtr, int x);
t_key		get_texture_index(t_ray *ray);
void		compute_wall_bounds(t_ray *ray);

/* ========================================================================== */
/*                               UTILS_FUNCTIONS                              */
/* ========================================================================== */

// print_debug
void		print_map(t_map *map);
void		print_elem(t_elem *elem);
void		print_cub_data(t_cub *cub);

// print_ray_debug
void		print_txtr_struct(t_txtr *txtr);
void		print_ray_info(t_ray *ray, int x);
void		print_updated_pos(t_cub *cub, t_player *player, char *key);

#endif