/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_game_mechanics2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:17:36 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/15 23:26:43 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	turn_left(t_cub *cub, t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	if (!player->display_cursor)
		player->rot_speed /= 1.5;
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(-player->rot_speed)
		- player->dir.y * sin(-player->rot_speed);
	player->dir.y = old_dir_x * sin(-player->rot_speed)
		+ player->dir.y * cos(-player->rot_speed);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(-player->rot_speed)
		- player->plane.y * sin(-player->rot_speed);
	player->plane.y = old_plane_x * sin(-player->rot_speed)
		+ player->plane.y * cos(-player->rot_speed);
	print_updated_pos(cub, player, "Left Arrow");
}

void	turn_right(t_cub *cub, t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	if (!player->display_cursor)
		player->rot_speed /= 1.5;
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(player->rot_speed)
		- player->dir.y * sin(player->rot_speed);
	player->dir.y = old_dir_x * sin(player->rot_speed)
		+ player->dir.y * cos(player->rot_speed);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(player->rot_speed)
		- player->plane.y * sin(player->rot_speed);
	player->plane.y = old_plane_x * sin(player->rot_speed)
		+ player->plane.y * cos(player->rot_speed);
	print_updated_pos(cub, player, "Right Arrow");
}

/*	player->pos.y is the rows
	player->pos.x is the cols
		map.grid[y][x]*/
bool	is_valid_move_x(t_cub *cub, t_player *player, double new_x)
{
	if (COLLISION)
		return (new_x >= 1 && new_x < cub->map.max_col
			&& cub->map.grid[(int)player->pos.y][(int)new_x] != '1');
	return (new_x >= 0 && new_x < cub->map.max_col
		&& player->pos.y >= 0
		&& player->pos.y < cub->map.rows
		&& new_x < ft_strlen(cub->map.grid[(int)player->pos.y]));
}

bool	is_valid_move_y(t_cub *cub, t_player *player, double new_y)
{
	if (COLLISION)
		return (new_y >= 1 && new_y < cub->map.rows
			&& cub->map.grid[(int)new_y][(int)player->pos.x] != '1');
	return (player->pos.x >= 0
		&& new_y >= 0
		&& new_y < cub->map.rows
		&& player->pos.x < ft_strlen(cub->map.grid[(int)new_y]));
}
