/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_game_mechanics2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:17:36 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/20 00:28:15 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* 2D rotation matrix:
	┌               ┐   ┌   ┐       ┌                     ┐
	│ cos(θ) -sin(θ)│   │ x │       │ x*cos(θ) - y*sin(θ) │
	│               │ × │   │   =   │                     │
	│ sin(θ)  cos(θ)│   │ y │       │ x*sin(θ) + y*cos(θ) │
	└               ┘   └   ┘       └                     ┘
*/
static t_vec	rotation_matrix(t_vec vec, double angle, bool mouse)
{
	t_vec	rotated;

	if (mouse)
		angle /= 1.5;
	rotated.x = vec.x * cos(angle) - vec.y * sin(angle);
	rotated.y = vec.x * sin(angle) + vec.y * cos(angle);
	return (rotated);
}

void	turn_left(t_cub *cub, t_player *player, bool mouse)
{
	player->dir = rotation_matrix(player->dir, -player->rot_speed, mouse);
	player->plane = rotation_matrix(player->plane, -player->rot_speed, mouse);
	print_updated_pos(cub, player, "Left Arrow");
}

void	turn_right(t_cub *cub, t_player *player, bool mouse)
{
	player->dir = rotation_matrix(player->dir, player->rot_speed, mouse);
	player->plane = rotation_matrix(player->plane, player->rot_speed, mouse);
	print_updated_pos(cub, player, "Right Arrow");
}

/*	player->pos.y is the rows
	player->pos.x is the cols
		map.grid[y][x]
*/
bool	is_valid_move_x(t_cub *cub, t_player *player, double new_x)
{
	if (COLLISION)
		return (new_x > 1 && new_x < cub->map.max_col - 1
			&& player->pos.y > 1
			&& player->pos.y < cub->map.rows - 1
			&& new_x < ft_strlen(cub->map.grid[(int)player->pos.y]) - 1
			&& cub->map.grid[(int)player->pos.y][(int)new_x] != '1');
	return (new_x >= 0 && new_x < cub->map.max_col
		&& player->pos.y >= 0
		&& player->pos.y < cub->map.rows
		&& new_x < ft_strlen(cub->map.grid[(int)player->pos.y]));
}

bool	is_valid_move_y(t_cub *cub, t_player *player, double new_y)
{
	if (COLLISION)
		return (player->pos.x > 1
			&& new_y > 1
			&& new_y < cub->map.rows - 1
			&& player->pos.x < ft_strlen(cub->map.grid[(int)new_y]) - 1
			&& cub->map.grid[(int)new_y][(int)player->pos.x] != '1');
	return (player->pos.x >= 0
		&& new_y >= 0
		&& new_y < cub->map.rows
		&& player->pos.x < ft_strlen(cub->map.grid[(int)new_y]));
}
