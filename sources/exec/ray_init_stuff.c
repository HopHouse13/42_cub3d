/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:01:42 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/22 20:36:16 by tjacquel         ###   ########.fr       */
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
	int	i;

	cub->mlx_pointer = NULL;
	cub->mlx_window = NULL;
	cub->game_img.mlx_img = NULL;
	i = -1;
	while (++i < 5)
		cub->txtr[i].mlx_img = NULL;
	i = -1;
	while (++i < 10)
		cub->sp_txtr[i].mlx_img = NULL;
	cub->doors = NULL;
	cub->sprites = NULL;
}

void	init_exec_data(t_cub *cub)
{
	init_ptr_to_null(cub);
	cub->map.display_map = true;
	cub->print_debug_cub = true;
	cub->game_init = true;
	cub->no_collision = false;
	cub->minimap_height = MNMAP_ROWS * MNMAP_TILE_SIZE;
	cub->minimap_width = MNMAP_COLS * MNMAP_TILE_SIZE;
}

void	init_player_time(t_cub *cub, t_player *player)
{
	player->old_time = player->time;
	player->time = date_in_ms(cub) - player->start_time;
	player->frame_time = (player->time - player->old_time) / 1000.0;
	player->move_speed = player->frame_time * 5.0;
	if (player->move_speed > 0.5)
		player->move_speed = 0.49;
	player->rot_speed = player->frame_time * 3.0;
	if (player->rot_speed > 0.5)
		player->rot_speed = 0.49;
}
