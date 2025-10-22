/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:28:01 by pbret             #+#    #+#             */
/*   Updated: 2025/10/23 00:52:13 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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
# include "error_bonus.h"
# include "macros_bonus.h"
# include "structs_bonus.h"

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
void		check_door(t_cub *cub);

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
void		render_2dray(t_cub *cub, t_player *player);
void		raycasting_loop(t_cub *cub, t_player *player, t_ray *ray);
void		render_map(t_cub *cub);
void		render(t_cub *cub);

// game_stuff
int			key_press_hook(int keysym, t_cub *cub);
int			key_release_hook(int keysym, t_cub *cub);
void		handle_move(t_cub *cub, t_player *player);
void		turn_right(t_cub *cub, t_player *player, bool mouse);
void		turn_left(t_cub *cub, t_player *player, bool mouse);
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
t_key		get_texture_index(t_cub *cub, t_ray *ray);
void		compute_wall_bounds(t_ray *ray);

/* ========================================================================== */
/*                               BONUS_FUNCTIONS                              */
/* ========================================================================== */

// mouse bonus
void		toggle_cursor_bonus(t_cub *cub);
void		mouse_mlx_hook_bonus(t_cub *cub);

// minimap bonus
void		draw_pixel_if_valid(t_cub *cub, int x, int y, int color);
void		get_map_center(t_cub *cub, t_vec *map_center);
double		get_map_scale(t_cub *cub);
t_vec		compute_2dray_impact(t_ray_buffer *buff, t_player *player);
void		draw_ray_line(t_cub *cub, t_coord start, t_coord end);

// door bonus
void		init_doors(t_cub *cub);
void		print_single_door(t_door *door);
bool		is_door_closed(t_cub *cub, int x, int y);
int			minimap_door_color(t_cub *cub, int x, int y);
void		door_interaction(t_cub *cub);
t_door		*which_door(t_cub *cub, int x, int y);
void		update_doors(t_cub *cub);
bool		should_ray_hit_door(t_cub *cub, t_ray *ray, t_door *door);

// sprites bonus
void		init_sprites(t_cub *cub);
void		init_sp_txtr(t_cub *cub);
void		update_all_sprites(t_cub *cub);
void		render_all_sprites(t_cub *cub);
void		render_single_sprite(t_cub *cub, t_sprite *sprite, int sp_idx);

// utils
int			add_fog(double distance, int pxl_color);
void		update_bonus(t_cub *cub);
void		render_bonus(t_cub *cub);
void		save_ray_buffer(t_cub *cub, t_ray *ray, int x);

/* ========================================================================== */
/*                               UTILS_FUNCTIONS                              */
/* ========================================================================== */

// print_debug
void		print_map(t_map *map);
void		print_elem(t_elem *elem);
void		print_cub_data(t_cub *cub);
void		print_sprites(t_cub *cub);
void		print_doors(t_cub *cub);

// print_ray_debug
void		print_sp_txtr_struct(t_txtr *sp_txtr);
void		print_txtr_struct(t_txtr *txtr);
void		print_ray_info(t_ray *ray, int x);
void		print_updated_pos(t_cub *cub, t_player *player, char *key);

#endif