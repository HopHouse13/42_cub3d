/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:47:43 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/22 15:56:52 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define SMOOTH 0
#define CHUNKY 1

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
void	update_door_state(t_door *door)
{
	if (door->state == OPENING)
	{
		door->offset += 1.0 / DOOR_ANIM_STEP;
		if (door->offset >= 1.0)
		{
			door->offset = 1.0;
			door->state = OPEN;
		}
	}
	else if (door->state == CLOSING)
	{
		door->offset -= 1.0 / DOOR_ANIM_STEP;
		if (door->offset <= 0.0)
		{
			door->offset = 0.0;
			door->state = CLOSED;
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
		return;
	last_update = current_time;
	i = 0;
	while (i < cub->elem.doors_nb)
	{
		update_door_state(&(cub->doors[i]));
		i++;
	}
}

t_door	*which_door(t_cub *cub, int x, int y)
{
	int	i;

	i = -1;
	while (++i < cub->elem.doors_nb)
	{
		if (cub->doors[i].pos.x == x && cub->doors[i].pos.y == y)
		{
			// if (cub->print_debug_cub)
			// 	printf("found door[%d] at {%d, %d}\n", i, cub->doors[i].pos.x, cub->doors[i].pos.y);
			return (&cub->doors[i]);
		}
	}
	return (NULL);
}

bool	is_door_closed(t_cub *cub, int x, int y)
{
	t_door	*door;

	door = which_door(cub, x, y);
	if (!door)
	{
		// if (cub->print_debug_cub)
		// 	printf("here\n");
		return (1);
	}
	return (door->state != OPEN);
}

int	minimap_door_color(t_cub *cub, int x, int y)
{
	if (is_door_closed(cub, x, y))
		return (RGB_ORG);
	else
		return (RGB_GRN);
}

void		door_interaction(t_cub *cub)
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
			door->action = true;
			print_doors(cub);
		}
	}
}

//void	count_doors(t_cub *cub)
//{
//	int		i;
//	int		j;

//	i = -1;
//	while (cub->map.grid[++i])
//	{
//		j = -1;
//		while (cub->map.grid[i][++j])
//		{
//			if (cub->map.grid[i][j] == 'D')
//				cub->elem.doors_nb++;
//		}
//	}
//}

void	init_doors(t_cub *cub)
{
	int		i;
	int		j;
	int		door_idx;

	door_idx = 0;
	//count_doors(cub);
	if (cub->elem.doors_nb == 0)
		return ;
	cub->doors = malloc(sizeof(t_door) * cub->elem.doors_nb);
	if (!cub->doors)
		cleanup_mlx(cub, MLX_OTHER_ERR);
	i = -1;
	while (cub->map.grid[++i])
	{
		j = -1;
		while (cub->map.grid[i][++j])
		{
			if (cub->map.grid[i][j] == 'D')
				cub->doors[door_idx++] = (t_door){(t_coord){j, i}, CLOSED, false, 0.0, 2.0};
		}
	}
	print_doors(cub);
}
