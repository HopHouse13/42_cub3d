/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_helper_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:14:18 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/22 16:15:35 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Calculate hit position within tile (0.0 to 1.0)
// When offset = 0: door covers full tile [0, 1]
// When offset = 1: door covers nothing
// Ray hits if it's in the covered portion
bool	should_ray_hit_door(t_cub *cub, t_ray *ray, t_door *door)
{
	double	hit_point;
	double	door_edge;

	if (ray->side == 0)
		hit_point = cub->player.pos.y + ray->ray_dir.y
					* (ray->side_dist.x - ray->delta_dist.x);
	else
		hit_point = cub->player.pos.x + ray->ray_dir.x
					* (ray->side_dist.y - ray->delta_dist.y);
	hit_point = hit_point - floor(hit_point);
	door_edge = 1.0 - door->offset;
	return (hit_point < door_edge);
}

t_door	*which_door(t_cub *cub, int x, int y)
{
	int	i;

	i = -1;
	while (++i < cub->elem.doors_nb)
	{
		if (cub->doors[i].pos.x == x && cub->doors[i].pos.y == y)
			return (&cub->doors[i]);
	}
	return (NULL);
}

bool	is_door_closed(t_cub *cub, int x, int y)
{
	t_door	*door;

	door = which_door(cub, x, y);
	if (!door)
		return (1);
	return (door->state != OPEN);
}

int	minimap_door_color(t_cub *cub, int x, int y)
{
	if (is_door_closed(cub, x, y))
		return (RGB_ORG);
	else
		return (RGB_GRN);
}
