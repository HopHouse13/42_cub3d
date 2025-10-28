/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_game_mechanics2_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:17:36 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/28 16:13:58 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

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
		angle /= MOUSE_SENSIVITY_RATIO;
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
bool	is_valid_move(t_cub *cub, double x, double y)
{
	t_door	*door;

	if (COLLISION)
	{
		if (x <= 1 || x >= cub->map.max_col - 1)
			return (false);
		if (y <= 1 || y >= cub->map.rows - 1
			|| x >= ft_strlen(cub->map.grid[(int)y]) - 1)
			return (false);
		if (cub->map.grid[(int)y][(int)x] == '1')
			return (false);
		if (BONUS && cub->map.grid[(int)y][(int)x] == 'D')
		{
			door = which_door(cub, (int)x, (int)y);
			return (door && door->state == OPEN);
		}
	}
	return (x >= 0 && x < cub->map.max_col
		&& y >= 0
		&& y < cub->map.rows
		&& x < ft_strlen(cub->map.grid[(int)y]));
}
