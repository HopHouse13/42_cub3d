/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:28:01 by pbret             #+#    #+#             */
/*   Updated: 2025/10/22 23:44:12 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"

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

// OPTIONS

# define MAP_VIEWPORT 1
# define MAP_SCALED 2

# define MAP_MODE 1
# define COLLISION 1
# define PRINT_DEBUG 0
# define BONUS 1
# define FOG 1

# define TILE_SIZE 64
# define PLAYER_SIZE 8

# define WNDW_W 1920
# define WNDW_H 1080

// Common minimap settings
# define MNMAP_MARGIN 10
#  define MNMAP_TILE_SIZE 16  // Fixed pixel size per tile
#  define MNMAP_COLS 32  // How many tiles wide
#  define MNMAP_ROWS 16  // How many tiles tall



# define RGB_WHT 0xFFFFFF
# define DARK_GREY 0x222222
# define RGG_BLCK 0x000000
# define RGB_RED 0xdb4437
# define RGB_BLUE 0x4285f4
# define RGB_YLW 0xf4b400
# define RGB_GRN 0x0f9d58
# define RGB_ORG 0xEC973D
# define DARK_BLUE 0x000067
# define RGB_FLOOR 0xC9C9C9
# define RGB_RAY_YLW 0xFFFF00
# define RGB_LIGHT_GREY 0xC9C9C9
# define LIGHT_GRN 0x98E48B
# define LIGHT_BLUE 0xAEEEEE
# define RGB_BEIGE 0xD2B48C

# define MOVE_SPEED 0.075
# define ROT_SPEED 0.035
# define MOVE_SPPED_MULT 5.0
# define ROT_SPEED_MULT 3.0
# define FOG_DISTANCE 8
# define FOG_COLOR RGG_BLCK
# define DOOR_ANIM_MS 60
# define DOOR_ANIM_STEP 8
# define DOOR_INTERACT 1.2
# define MAX_SPRITES 100
# define SP_FRAMES 10

/* *************************************** ERRORS MESSAGE ************************************ */

# define OK						"Cub3D executed successfully"
# define PSG_FILENAME_ERR		"Invalid file name"
# define PSG_OPEN_FILE_ERR		"Unable to open the .cub file"
# define PSG_READ_FILE_ERR		"Unable to read the .cub file"
# define PSG_MISS_PARAM_ERR		"Missing parameters"
# define PSG_NO_KEY_ERR			"Missing map elements"
# define PSG_LINE_FT_ERR		"Invalid line format"
# define PSG_DUP_PATH_ERR		"Duplicate texture path definition"
# define PSG_DUP_COLOR_ERR		"Duplicate color definition"
# define PSG_PATH_ERR			"Unable to open texture file"
# define PSG_READ_PATH_ERR		"Unable to read texture file"
# define PSG_OVERFLOW_ERR 		"Integer value exceeds the allowed range"
# define PSG_RGB_FT_ERR			"Invalid RGB format"
# define PSG_EMPTY_MAP_ERR		"Map is empty"
# define PSG_INV_CHAR_MAP_ERR	"Invalid character found in map"
# define PSG_DUP_PLAYER_ERR		"Multiple player start positions found"
# define PSG_EMPTY_LINE_ERR		"Empty line inside map"
# define PSG_OPEN_MAP_ERR		"Map is not enclosed"
# define PSG_NO_PLAYER_ERR		"No player on the map"
# define PSG_DOOR_ERR			"Invalid door on the map"
# define PSG_SP_MAX_ERR			"Too many sprites"
# define MLX_TXTR_ERR			"Unable to initialize the textures"
# define MLX_IMG_ERR			"Unable to initialize the images"
# define MLX_PTR_ERR			"MLX initialization failed"
# define MLX_WDW_ERR			"Window creation failed"
# define ALLOC_ERR				"Memory allocation failed"
# define MLX_OTHER_ERR			"PLACEHOLDER"             // pour le debug
# define UNKNOWN_ERR			"Unknown error occurred"

/* ************************************** RAYCASTER STRUCTS ********************************** */

typedef enum	e_door_state
{
	CLOSED,
	CLOSING,
	OPENING,
	OPEN,
}				t_door_state;

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
				DO,
				s0,
				s1,
				s2,
				s3,
				s4,
				s5,
				s6,
				s7,
				s8,
				s9,
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

typedef struct	s_pxl_range
{
	t_coord		start;
	t_coord		end;
}				t_pxl_range;

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

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
	char		*path[15]; // 0 NO, 1 EA, 2 SO, 3 WE, 4 DO, 5=s0, 6=s1, 7=s2, 8=s3, 9=s4, 10=s5, 11=s6, 12=s7, 13=s8, 14=s9
	int			f_values[3];
	int			c_values[3];
	int			f_color;
	int			c_color;
	char		facing; //dir
	bool		start_line;
	int			e_counter;
	int			doors_nb;
	int			sprite_nb;
}				t_elem;

typedef struct	s_txtr
{
	void		*mlx_img;
	char		*addr;
	int			bpp; /* bits per pixel */
	int			line_len;
	int			endian;
	int			width;
	int			height;
	t_coord		pxl;
}			t_txtr;

typedef struct	s_psg
{
	int			fd_file;
	char		*line;
}				t_psg;

typedef struct s_door
{
	t_coord			pos;
	t_door_state	state;
	bool			print_debug;
	double			offset;
}				t_door;

typedef struct s_sp_sort
{
	int		sprite_idx;
	double	distance;
}			t_sp_sort;

typedef struct s_sp_render
{
	t_vec		rel_pos;
	t_vec		transform;
	double		inv_det;
	int			screen_x;
	int			height;
	int			width;
	t_coord		txtr;
	t_pxl_range	draw;
	t_coord		pxl;
}				t_sp_render;

typedef struct s_sprite
{
	t_vec		pos;
	bool		active;
	int			current_frame;
	double		frame_duration;
	double		elapsed_time;
	double		distance;
	bool		loop;
	bool		print_debug;
}				t_sprite;

typedef struct s_ray_buffer
{
	t_coord		map;
	t_vec		ray_dir;
	t_coord		step;
	int			side;
	double		perp_wall_dist;
}				t_ray_buffer;



typedef struct	s_cub
{
	void		*mlx_pointer;
	void		*mlx_window;
	t_txtr		txtr[5];
	t_txtr		sp_txtr[10];


	int			minimap_height;
	int			minimap_width;

	t_map		map;
	t_elem		elem;
	t_player	player;

	t_img		game_img;

	t_door		*doors;
	t_sprite	*sprites;
	// double		z_buffer[WNDW_W];
	t_ray_buffer	buff[WNDW_W];

	t_psg		psg;

	bool		game_init;		// debug
	bool		print_debug_cub; // debug
	bool		no_collision;
}				t_cub;

typedef struct	s_ray
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
}				t_ray;





/// PARSING ///
void	parsing(t_cub *cub, char *argv);
void	init_parsing_data(t_cub *cub);

// PARSING_CHECK_FILENAME ///
void	check_filename(t_cub *cub, char *argv);

// PARSING_CHECK_ELEM //
void	check_elem(t_cub *cub, char *file_map);
void	handle_paths(t_cub *cub, char **line, t_key key_id);
void	handle_colors(t_cub *cub, char **line, t_key key_id);

// PARSING_CHECK_MAP ///
void	make_copy(t_cub *cub, char *mapfile);
void	check_map(t_cub *cub, char *mapfile);
void	empty_line(t_cub *cub);
void	check_door(t_cub *cub);

/// UTILITIES ///
void	exit_door(t_cub *cub, char *err_id, char *item);
void	init_err_msgs(t_cub *cub);

/// PARSING_UTILITIES ///
char	*get_next_line(int fd, char **err_id, bool exit_door);
char	*gnl_strdup(const char *s, char **err_id);
char	*gnl_strjoin(const char *s1, const char *s2, char **err_id);

// print_debug
void	print_cub_data(t_cub *cub);
void	print_elem(t_elem *elem);
void	print_map(t_map *map);

/* ************************************** RAYCASTER FCTIONS ********************************** */
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
void		print_ray_info(t_ray *ray, int x);
void		print_updated_pos(t_cub *cub, t_player *player, char *key);
void		turn_right(t_cub *cub, t_player *player, bool mouse);
void		turn_left(t_cub *cub, t_player *player, bool mouse);
bool		is_valid_move_x(t_cub *cub, t_player *player, double new_x);
bool		is_valid_move_y(t_cub *cub, t_player *player, double new_y);
bool		is_valid_move(t_cub *cub, double x, double y);









// utils
uint32_t	char_to_tile_rgb(char c);
void		print_map_ray(t_map *map);
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


// bonus
// int			handle_mouse(int x, int y, t_cub *cub);
// int			handle_focus_out(t_cub *cub);
// int			handle_focus_in(t_cub *cub);
void		toggle_cursor_bonus(t_cub *cub);
void		mouse_mlx_hook_bonus(t_cub *cub);


void		draw_pixel_if_valid(t_cub *cub, int x, int y, int color);
void		get_map_center(t_cub *cub, t_vec *map_center);
double		get_map_scale(t_cub *cub);
bool		is_in_minimap_circle(int x, int y);
bool		ray_outside_minimap(t_cub *cub, t_ray *ray);
t_vec		compute_2dray_impact(t_ray_buffer *buff, t_player *player);
void		draw_ray_line(t_cub *cub, t_coord start, t_coord end);



int			add_fog(double distance, int pxl_color);
void		init_doors(t_cub *cub);
void		print_doors(t_cub *cub);
void		print_single_door(t_door *door);
bool		is_door_closed(t_cub *cub, int x, int y);
int			minimap_door_color(t_cub *cub, int x, int y);
void		door_interaction(t_cub *cub);
t_door		*which_door(t_cub *cub, int x, int y);
void		update_doors(t_cub *cub);
bool		should_ray_hit_door(t_cub *cub, t_ray *ray, t_door *door);

void		init_sprites(t_cub *cub);
void		count_sprites(t_cub *cub);

void		print_sprites(t_cub *cub);
void		init_sp_txtr(t_cub *cub);
void		print_sp_txtr_struct(t_txtr *txtr);
void		update_all_sprites(t_cub *cub);
void		render_all_sprites(t_cub *cub);
void		render_single_sprite(t_cub *cub, t_sprite *sprite, int sp_idx);

void		update_bonus(t_cub *cub);
void		render_bonus(t_cub *cub);
void		save_ray_buffer(t_cub *cub, t_ray *ray, int x);













/* ************************************** RAYCASTER FCTIONS END ********************************** */

#endif