/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:28:01 by pbret             #+#    #+#             */
/*   Updated: 2025/10/06 20:05:33 by tjacquel         ###   ########.fr       */
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

# define RGB_WHT 0xFFFFFF
# define RGB_RED 0xdb4437
# define RGB_BLUE 0x4285f4
# define RGB_YLW 0xf4b400
# define RGB_GRN 0x0f9d58
# define RGB_SKY 0x8786C0
// # define RGB_FLR 0x927A8B
# define RGB_FLR 0xC08786

# define P_FLOOR "../textures/green_texture.xpm"
# define P_WALL "../textures/red_texture.xpm"
# define P_EP "../textures/yellowE_texture.xpm"
# define P_SP "../textures/yellowS_texture.xpm"
# define P_WP "../textures/yellowW_texture.xpm"
# define P_NP "../textures/yellowN_texture.xpm"
# define P_EXTRA "../textures/blue_texture.xpm"
# define P_GRASS "../textures/floor_texture.xpm"
# define P_SKY "../textures/sky_texture.xpm"

# define FOV 66


/* ************************************** RAYCASTER STRUCTS ********************************** */

typedef enum	e_tile
{
	E_FLOOR,
	E_WALL,
	E_EP,
	E_SP,
	E_WP,
	E_NP,
	E_EXTRA
}			t_tile;

typedef struct s_map_ray
{
	char		grid[8][8];
	size_t		rows;
	size_t		cols;
}				t_map_ray;

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


typedef struct s_mlx_data
{
	void		*mlx_pointer;
	void		*mlx_window;
	// void		*mlx_minimap;
	void		*textures[7];
	void		*bckgr_txtr[2];
	int			img_height;
	int			img_width;
	int			window_height;
	int			window_width;
	int			moves;
	t_map_ray	map;
	bool		display_map;


	t_img		map_img;
	// t_img		background_img;
	t_img		game_img;

	// void		*ray_image; 		// en gros ce bloc a ete bouge dans t_img
	// char		*ray_data;
	// int		ray_bits_per_pixel;
	// int		ray_line_length;
	// int		ray_endian;

	// t_elements	*elts;
}			t_mlx_data;

typedef struct s_coord
{
	double	x;
	double	y;
}				t_coord;


typedef struct s_player_data
{
	//t_coord		pos;
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double		start_time;
	double		time;
	double		old_time;
	double		frameTime;
	double		cameraX;

	// more like ray cub
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;

	double		moveSpeed;
	double		rotSpeed;

	bool		print_debug;	// debug
	bool		game_init;		// debug


	t_key_inpt	kbrd;


	t_mlx_data	*mlx_data_pointer;

}			t_player_data;

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

	char		facing;

	double		start_time;
	double		time;			// a voir si on peut passer cette variable en local
	double		old_time;		// a voir si on peut passer cette variable en local
	double		frame_time;		// a voir si on peut passer cette variable en local

	double		camera_x;		// a voir si on peut passer cette variable en local

	double		rot_speed;
	double		move_speed;		// struct ray ou player?

	t_key_inpt	kbrd;




}				t_player;

typedef struct	s_map
{
	char 		**grid;
	size_t		rows;
	size_t		cols;
	bool		display_map;
}				t_map;

typedef struct	s_elements
{
	char		*path[4]; // 0 NO, 1 EA, 2 SO, 3 WE
	int			f_value[3]; // init a -1 car 0 valeur accepte
	int			c_value[3];
	char		facing;
	bool		start_line;
	int			e_counter;
}				t_elem;

typedef struct	s_cub
{
	void		*mlx_pointer;
	void		*mlx_window;
	void		*textures[7];
	int			img_height;
	int			img_width;
	int			moves;

	int			window_height;
	int			window_width;

	t_map		map;
	t_elem		elem;
	t_player	player;

	t_img		map_img;
	t_img		game_img;


	int			fd_file;
	char		*err_msg[E_UNKNOWN + 1];
}			t_cub;

typedef struct s_ray
{
	t_vec		map;
	t_vec		ray_dir;
	t_vec		delta_dist;
	t_vec		side_dist;
	t_vec		step;
	double		perp_wall_dist;
	int			hit;
	int			side;

	bool		print_debug;	// debug
	bool		game_init;		// debug
}			t_ray;

/// PARSING ///
void	parsing(t_cub *cub, char *argv);
void	check_filename(t_cub *cub, char *argv);
void	check_elem(t_cub *cub, char *file_map);

void	check_map(t_cub *cub, char *mapfile);
void	make_copy(t_cub *cub, char *mapfile);
bool	is_empty(char *line);

/// UTILITIES ///

// handle_exit
void	exit_door(t_cub *cub, t_error err_id);

// init_cub_data
void	init_cub_data(t_cub *cub);
void	init_elem(t_elem *elem);

// GNL
char	*get_next_line(int fd, t_error *err_id, bool exit_door);
char	*gnl_strdup(const char *s, t_error *err_id);
char	*gnl_strjoin(const char *s1, const char *s2, t_error *err_id);

// print_debug
void	print_cub_data(t_cub *cub);
void	print_elem(t_elem *elem);
void	print_map(char **map);

/* ************************************** RAYCASTER FCTIONS ********************************** */
// init_stuff
int			exec_launch(t_cub *cub);
// void		init_textures(t_mlx_data *data);
void		init_exec_data(t_cub *cub);
int			init_player(t_cub *cub, t_player *player);
void		init_images(t_cub *cub);
void		init_ray_data(t_ray *ray);




// mlx_stuff
int			close_window(t_cub *cub);
void		clear_img(t_img *img, int width, int height);
void		cleanup_mlx(t_cub *cub);




// render_stuff
void		render_map(t_cub *cub, t_player *player);
bool		render(t_cub *cub);

// game_stuff
int			key_press_hook(int keysym, t_cub *cub);
int			key_release_hook(int keysym, t_cub *cub);
void		handle_move(t_cub *cub, t_player *player, t_ray *ray);
void		print_ray_info(t_ray *ray, int x, FILE *fp);
void		print_updated_pos(t_player *player, t_ray *ray);




// utils
t_tile		char_to_tile(char c);
void		print_map_ray(t_map *map);
double		date_in_s(void);
double		date_in_ms(void);

// render utils
void		img_pix_put(t_img *img, int x, int y, int color);
int			render_empty_sqr(t_img *img, t_sqr sqr);
int			render_sqr(t_img *img, t_sqr sqr);
int			render_rect(t_img *img, t_rect rect);


/* ************************************** RAYCASTER FCTIONS END ********************************** */

#endif