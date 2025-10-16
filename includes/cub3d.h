/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:28:01 by pbret             #+#    #+#             */
/*   Updated: 2025/10/17 00:24:00 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "error.h"

# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <float.h>
# include <sys/time.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <string.h>
# include "mlx.h"

# define TILE_SIZE 64
# define PLAYER_SIZE 8

# define WNDW_W 1920
# define WNDW_H 1080
# define MINIMAP_H (WNDW_H / 5)
# define MINIMAP_W (WNDW_W / 5)

# define MINIMAP_SIZE 200
# define MINIMAP_MARGIN 20
# define MINIMAP_RADIUS 5
# define MINIMAP_TILE_SIZE (MINIMAP_SIZE / (MINIMAP_RADIUS * 2 + 1))

# define RGB_WHT 0xFFFFFF
# define RGB_RED 0xdb4437
# define RGB_BLUE 0x4285f4
# define RGB_YLW 0xf4b400
# define RGB_GRN 0x0f9d58
# define RGB_FLOOR 0x0000067

# define MOVE_SPEED 0.075
# define ROT_SPEED 0.035

# define FOV 66
#  if FOV <= 0 || FOV >= 180
#   error "FOV must be between 0 and 180 degrees (exclusive)"
#  endif

# define FOV_RAD (FOV * M_PI / 180.0)
# define PLANE_MAG (round(tan(FOV_RAD / 2.0) * 100.0) / 100.0)

# define MAP_RATIO 2
// #  if MAP_RATIO <= 0 || MAP_RATIO >= 10
// #  error "MAP_RATIO must be between 0 and 10 (exclusive)"
// #  endif

# define COLLISION 1
# define PRINT_DEBUG 0


/* ************************************** RAYCASTER STRUCTS ********************************** */

typedef enum	e_tile
{
	TILE_FLOOR,
	TILE_WALL,
	TILE_EP,
	TILE_SP,
	TILE_WP,
	TILE_NP,
	TILE_EXTRA
}			t_tile;

typedef struct	s_img
{
	void		*mlx_img;
	char		*addr;
	int			bpp; /* bits per pixel */
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_key_inpt
{
	bool		key_w;
	bool		key_s;
	bool		key_a;
	bool		key_d;
	bool		key_left;
	bool		key_right;
	bool		key_m;

}				t_key_inpt;

typedef struct s_sqr
{
	int			x;
	int			y;
	int			side;
	int			color;
}				t_sqr;

typedef struct s_rect
{
	int			x;
	int			y;
	int			width;
	int			height;
	int			color;
}				t_rect;
/* ************************************** RAYCASTER STRUCTS END ********************************** */

typedef enum	e_key
{
				NO,
				EA,
				SO,
				WE,
				F,
				C,
}				t_key;

typedef struct	s_coord
{
	int		x;
	int		y;
}				t_coord;

typedef struct	s_vec
{
	double		x;
	double		y;
}				t_vec;

typedef struct	s_player
{
	t_vec		pos;
	t_vec		dir;
	t_vec		plane;

	double		start_time;
	double		time;			// a voir si on peut passer cette variable en local
	double		old_time;		// a voir si on peut passer cette variable en local
	double		frame_time;		// a voir si on peut passer cette variable en local

	// double		camera_x;		// a voir si on peut passer cette variable en local

	double		rot_speed;		// a passer en macro fixe ?
	double		move_speed;		// struct ray ou player? // ou plutot  a passer en macro fixe ?

	bool 		display_cursor;
	bool		cursor_hidden;

	int			moves;

	t_key_inpt	kbrd;

}				t_player;

typedef struct	s_map
{
	char 		**grid;
	size_t		rows;
	size_t		max_col;
	bool		display_map;
}				t_map;

typedef struct	s_elements
{
	char		*path[4]; // 0 NO, 1 EA, 2 SO, 3 WE
	int			f_values[3];
	int			c_values[3];
	int			f_color;
	int			c_color;
	char		facing; //dir
	bool		start_line;
	int			e_counter;
}				t_elem;

typedef struct s_txtr
{
	void		*mlx_img; // ca x4
	char		*addr;
	int			bpp; /* bits per pixel */
	int			line_len;
	int			endian;
	int			width;
	int			height;
	t_coord		pxl;
}			t_txtr;


typedef struct	s_cub
{
	void		*mlx_pointer; // ca
	void		*mlx_window; // ca
	t_txtr		txtr[4]; // ca

	int			window_height;
	int			window_width;

	t_map		map;
	t_elem		elem;
	t_player	player;

	t_img		map_img; // ca
	t_img		game_img; // ca

	int			fd_file;
	char		*err_msg[UNKNOWN_ERR + 1];

	bool		game_init;		// debug
	bool		print_debug_cub; // debug
	bool		render_bool;
	bool		no_collision;
}			t_cub;

typedef struct s_ray
{
	t_coord		map;
	t_vec		ray_dir;
	t_vec		delta_dist;
	t_vec		side_dist;
	t_coord		step;
	double		perp_wall_dist;
	double		wall_x;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;

}			t_ray;

/// PARSING ///
void	parsing(t_cub *cub, char *argv);

// PARSING_CHECK_FILENAME ///
void	check_filename(t_cub *cub, char *argv);

// PARSING_CHECK_ELEM //
void	check_elem(t_cub *cub, char *file_map);
t_error	handle_paths(t_cub *cub, char **line, t_key key_id);
t_error	handle_colors(t_cub *cub, char **line, t_key key_id);

// PARSING_CHECK_MAP ///
void	check_map(t_cub *cub, char *mapfile);
void	make_copy(t_cub *cub, char *mapfile);
bool	open_cell(t_cub *cub, char **map, int i, int j);
void	valid_outline(t_cub *cub);
void	valid_char(t_cub *cub);
void	get_player(t_cub *cub);
void	empty_line(t_cub *cub);

/// UTILITIES ///
void	exit_door(t_cub *cub, t_error err_id, char *str);
void	init_err_msgs(t_cub *cub);

/// PARSING_UTILITIES ///
void	init_parsing_data(t_cub *cub);
char	*supp_newline(t_cub *cub, char *line);
char	*get_next_line(int fd, t_error *err_id, bool exit_door);
char	*gnl_strdup(const char *s, t_error *err_id);
char	*gnl_strjoin(const char *s1, const char *s2, t_error *err_id);

// print_debug
void	print_cub_data(t_cub *cub);
void	print_elem(t_elem *elem);
void	print_map(char **map);

/* ************************************** RAYCASTER FCTIONS ********************************** */
// init_stuff
void		exec_launch(t_cub *cub);
void		init_textures(t_cub *cub);
void		init_exec_data(t_cub *cub);
void		init_player(t_cub *cub, t_player *player);
void		init_images(t_cub *cub);
void		init_ray_data(t_ray *ray);

// mlx_stuff
void		cleanup_mlx(t_cub *cub, t_error mlx_err, char *str);

// render_stuff
void		render_cubes(t_cub *cub, t_player *player, t_ray *ray, int x);
void		render_2dray(t_cub *cub, t_player *player, t_ray *ray);
void		raycasting_loop(t_cub *cub, t_player *player, t_ray *ray);
void		render_map(t_cub *cub);
void		render(t_cub *cub);

// game_stuff
int			key_press_hook(int keysym, t_cub *cub);
int			key_release_hook(int keysym, t_cub *cub);
void		handle_move(t_cub *cub, t_player *player);
void		print_ray_info(t_ray *ray, int x, FILE *fp);
void		print_updated_pos(t_cub *cub, t_player *player, char *key);
void		turn_right(t_cub *cub, t_player *player, bool mouse);
void		turn_left(t_cub *cub, t_player *player, bool mouse);
bool		is_valid_move_x(t_cub *cub, t_player *player, double new_x);
bool		is_valid_move_y(t_cub *cub, t_player *player, double new_y);








// utils
t_tile		char_to_tile(char c);
void		print_map_ray(t_map *map);
double		date_in_s(t_cub *cub);
double		date_in_ms(t_cub *cub);
void		print_txtr_struct(t_txtr *txtr);


// render utils
void		img_pxl_put(t_img *img, int x, int y, int color);

int			render_empty_sqr(t_img *img, t_sqr sqr);
int			render_sqr(t_img *img, t_sqr sqr);
int			render_rect(t_img *img, t_rect rect);

// render textures
void		render_texture(t_cub *cub, t_ray *ray, t_txtr *txtr, int x);
t_key		get_texture_index(t_ray *ray);
void		compute_wall_bounds(t_ray *ray);


// bonus
int		handle_mouse(int x, int y, t_cub *cub);
int		handle_focus_out(t_cub *cub);
int		handle_focus_in(t_cub *cub);
void	toggle_cursor_bonus(t_cub *cub);
void	mouse_mlx_hook_bonus(t_cub *cub);



/* ************************************** RAYCASTER FCTIONS END ********************************** */

#endif