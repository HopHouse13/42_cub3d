/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:11:05 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/28 18:06:16 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

/* ========================================================================== */
/*                                    ENUMS                                   */
/* ========================================================================== */

typedef enum e_key
{
	NO,
	EA,
	SO,
	WE,
	F,
	C,
}			t_key;

/* ========================================================================== */
/*                                HELPER_STRUCTS                              */
/* ========================================================================== */

typedef struct s_coord
{
	int				x;
	int				y;
}					t_coord;

typedef struct s_vec
{
	double			x;
	double			y;
}					t_vec;

typedef struct s_pxl_range
{
	t_coord			start;
	t_coord			end;
}					t_pxl_range;

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct s_sqr
{
	int				x;
	int				y;
	int				side;
	int				color;
}					t_sqr;

typedef struct s_rect
{
	int				x;
	int				y;
	int				width;
	int				height;
	int				color;
}					t_rect;

/* ========================================================================== */
/*                                  GAME_STRUCTS                              */
/* ========================================================================== */

typedef struct s_img
{
	void			*mlx_img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_key_inpt
{
	bool			key_w;
	bool			key_s;
	bool			key_a;
	bool			key_d;
	bool			key_left;
	bool			key_right;
}					t_key_inpt;

typedef struct s_player
{
	t_vec			pos;
	t_vec			dir;
	t_vec			plane;
	double			start_time;
	double			time;
	double			old_time;
	double			frame_time;
	double			rot_speed;
	double			move_speed;
	int				moves;
	t_key_inpt		kbrd;
}					t_player;

typedef struct s_map
{
	char			**grid;
	size_t			rows;
	size_t			max_col;
}					t_map;

typedef struct s_elements
{
	char			*path[4];
	int				f_values[3];
	int				c_values[3];
	int				f_color;
	int				c_color;
	char			facing;
	bool			start_line;
	int				e_counter;
}					t_elem;

typedef struct s_txtr
{
	void			*mlx_img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
	t_coord			pxl;
}					t_txtr;

typedef struct s_psg
{
	int				tmp_fd;
	int				tmp_read;
	int				fd_file;
	char			*line;
}					t_psg;

typedef struct s_cub
{
	void			*mlx_pointer;
	void			*mlx_window;
	t_txtr			txtr[4];
	t_map			map;
	t_elem			elem;
	t_player		player;
	t_img			game_img;
	t_psg			psg;
	bool			game_init;
	bool			print_debug_cub;
}					t_cub;

typedef struct s_ray
{
	t_coord			map;
	t_vec			ray_dir;
	t_vec			delta_dist;
	t_vec			side_dist;
	t_coord			step;
	double			perp_wall_dist;
	double			wall_x;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

#endif