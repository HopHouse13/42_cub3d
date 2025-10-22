/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:47:43 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/22 22:04:09 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	update_door_state(t_cub *cub, t_door *door)
{
	if (door->state == OPENING)
	{
		door->offset += 1.0 / DOOR_ANIM_STEP;
		if (door->offset >= 1.0)
		{
			door->offset = 1.0;
			door->state = OPEN;
			door->print_debug = true;
			print_doors(cub);
		}
	}
	else if (door->state == CLOSING)
	{
		door->offset -= 1.0 / DOOR_ANIM_STEP;
		if (door->offset <= 0.0)
		{
			door->offset = 0.0;
			door->state = CLOSED;
			door->print_debug = true;
			print_doors(cub);
		}
	}
}

void	update_doors(t_cub *cub)
{
	int				i;
	static double	last_update = 0;
	double			current_time;

	current_time = cub->player.time;
	if (current_time - last_update < DOOR_ANIM_MS)
		return ;
	last_update = current_time;
	i = 0;
	while (i < cub->elem.doors_nb)
	{
		update_door_state(cub, &(cub->doors[i]));
		i++;
	}
}

void	door_interaction(t_cub *cub)
{
	int		door_x;
	int		door_y;
	t_door	*door;

	door_x = (int)(cub->player.pos.x + cub->player.dir.x * DOOR_INTERACT);
	door_y = (int)(cub->player.pos.y + cub->player.dir.y * DOOR_INTERACT);
	if (door_y >= 0 && door_y < (int)cub->map.rows
		&& door_x >= 0 && door_x < (int)ft_strlen(cub->map.grid[door_y]))
	{
		door = which_door(cub, door_x, door_y);
		if (door)
		{
			if (door->state == CLOSED)
				door->state = OPENING;
			else if (door->state == OPEN)
				door->state = CLOSING;
			else if (door->state == OPENING)
				door->state = CLOSING;
			else if (door->state == CLOSING)
				door->state = OPENING;
			door->print_debug = true;
			print_doors(cub);
		}
	}
}

void	init_doors(t_cub *cub)
{
	int		i;
	int		j;
	int		door_idx;

	door_idx = 0;
	if (cub->elem.doors_nb == 0)
		return ;
	cub->doors = malloc(sizeof(t_door) * cub->elem.doors_nb);
	if (!cub->doors)
		cleanup_mlx(cub, PSG_ALLOC_ERR);
	i = -1;
	while (cub->map.grid[++i])
	{
		j = -1;
		while (cub->map.grid[i][++j])
		{
			if (cub->map.grid[i][j] == 'D')
				cub->doors[door_idx++]
					= (t_door){(t_coord){j, i}, CLOSED, false, 0.0};
		}
	}
	print_doors(cub);
}
