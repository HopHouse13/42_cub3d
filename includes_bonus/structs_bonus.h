/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:11:05 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/23 01:38:50 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

# include "cub3d_bonus.h"

/* ========================================================================== */
/*                                    ENUMS                                   */
/* ========================================================================== */

typedef enum e_door_state
{
	CLOSED,
	CLOSING,
	OPENING,
	OPEN,
}					t_door_state;

typedef enum e_key
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
}					t_key;

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
	bool			key_m;

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
	bool			display_cursor;
	bool			cursor_hidden;
	int				moves;
	t_key_inpt		kbrd;
}					t_player;

typedef struct s_map
{
	char			**grid;
	size_t			rows;
	size_t			max_col;
	bool			display_map;
}					t_map;

typedef struct s_elements
{
	char			*path[15];
	int				f_values[3];
	int				c_values[3];
	int				f_color;
	int				c_color;
	char			facing;
	bool			start_line;
	int				e_counter;
	int				doors_nb;
	int				sprite_nb;
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
	int				fd_file;
	char			*line;
}					t_psg;

typedef struct s_door
{
	t_coord			pos;
	t_door_state	state;
	bool			print_debug;
	double			offset;
}					t_door;

typedef struct s_sp_sort
{
	int				sprite_idx;
	double			distance;
}					t_sp_sort;

typedef struct s_sp_render
{
	t_vec			rel_pos;
	t_vec			transform;
	double			inv_det;
	int				screen_x;
	int				height;
	int				width;
	t_coord			txtr;
	t_pxl_range		draw;
	t_coord			pxl;
}					t_sp_render;

typedef struct s_sprite
{
	t_vec			pos;
	bool			active;
	int				current_frame;
	double			frame_duration;
	double			elapsed_time;
	double			distance;
	bool			loop;
	bool			print_debug;
}					t_sprite;

typedef struct s_ray_buffer
{
	t_coord			map;
	t_vec			ray_dir;
	t_coord			step;
	int				side;
	double			perp_wall_dist;
}					t_ray_buffer;

typedef struct s_cub
{
	void			*mlx_pointer;
	void			*mlx_window;
	t_txtr			txtr[5];
	t_txtr			sp_txtr[10];
	int				minimap_height;
	int				minimap_width;
	t_map			map;
	t_elem			elem;
	t_player		player;
	t_img			game_img;
	t_door			*doors;
	t_sprite		*sprites;
	t_ray_buffer	buff[WNDW_W];
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