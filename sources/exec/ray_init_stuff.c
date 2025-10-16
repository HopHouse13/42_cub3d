/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:01:42 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/16 22:12:34 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	which_starting_direction(t_player *player, char facing)
{
	if (facing == 'W')
	{
		player->dir = (t_vec){-1, 0};
		player->plane = (t_vec){0, -0.66};
	}
	if (facing == 'E')
	{
		player->dir = (t_vec){1, 0};
		player->plane = (t_vec){0, 0.66};
	}
	if (facing == 'N')
	{
		player->dir = (t_vec){0, -1};
		player->plane = (t_vec){0.66, 0};
	}
	if (facing == 'S')
	{
		player->dir = (t_vec){0, 1};
		player->plane = (t_vec){-0.66, 0};
	}
}

void	init_player(t_cub *cub, t_player *player)
{
	player->pos.x += 0.5;
	player->pos.y += 0.5;
	which_starting_direction(player, cub->elem.facing);
	player->start_time = date_in_ms(cub);
	player->time = 0;
	player->old_time = 0;
	player->frame_time = 0;
	player->rot_speed = 0;
	player->move_speed = 0;
	player->kbrd = (t_key_inpt){0, 0, 0, 0, 0, 0, 1};
	player->display_cursor = true;
	player->cursor_hidden = false;
	player->moves = 0;
	print_map_ray(&(cub->map));
	print_elem(&(cub->elem));
}

static void	init_ptr_to_null(t_cub *cub)
{
	size_t	i;

	cub->mlx_pointer = NULL;
	cub->mlx_window = NULL;
	cub->map_img.mlx_img = NULL;
	cub->game_img.mlx_img = NULL;
	i = -1;
	while (++i < 4)
		cub->txtr[i].mlx_img = NULL;
}

void	init_exec_data(t_cub *cub)
{
	init_ptr_to_null(cub);
	cub->window_width = (cub->map).max_col * TILE_SIZE / MAP_RATIO;
	cub->window_height = (cub->map).rows * TILE_SIZE / MAP_RATIO;
	cub->map.display_map = true;
	cub->print_debug_cub = true;
	cub->game_init = true;
	cub->render_bool = true;
	cub->no_collision = false;
}
