/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:41:15 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/20 00:59:16 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	outofbounds_dda_ray(t_cub *cub, t_ray *ray)
{
	if (ray->map.y < 0
		|| ray->map.y >= (int)cub->map.rows)
	{
		ray->hit = 1;
		return (true);
	}
	if (ray->map.x < 0
		|| ray->map.x >= (int)ft_strlen(cub->map.grid[ray->map.y]))
	{
		ray->hit = 1;
		return (true);
	}
	return (false);
}


/* 6. Digital Differential Analysis: Casting the ray */
static void	dda_loop(t_cub *cub, t_ray *ray, bool render_map)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (outofbounds_dda_ray(cub, ray))
			break ;
		if (BONUS && render_map && ray_outside_minimap(cub, ray))
			ray->hit = 1;
		if (cub->map.grid[ray->map.y][ray->map.x] == '1')
			ray->hit = 1;
	}
}

/* 5. Calculation of steps and initial side distances  */
static void	init_step_and_sidedist(t_player *player, t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x
			= (player->pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x
			= (ray->map.x + 1.0 - player->pos.x) * ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y
			= (player->pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y
			= (ray->map.y + 1.0 - player->pos.y) * ray->delta_dist.y;
	}
}

static double	compute_delta_dist(double ray_dir)
{
	if (ray_dir == 0)
		return (1e30);
	return (fabs(1 / ray_dir));
}

/*
1. x is the index of the column to render
2.	Ray calculation for column x (camera_x, ray_dir)
3. Position in the grid (map)
4. Initial distances (delta_dist)
 */
void	raycasting_loop(t_cub *cub, t_player *player, t_ray *ray, bool render_map)
{
	int		x;
	double	camera_x;

	x = 0;
	while (x < WNDW_W)
	{
		camera_x = 2 * x / (double)WNDW_W - 1;
		ray->ray_dir.x = player->dir.x + player->plane.x * camera_x;
		ray->ray_dir.y = player->dir.y + player->plane.y * camera_x;
		ray->map.x = (int)player->pos.x;
		ray->map.y = (int)player->pos.y;
		ray->delta_dist.x = compute_delta_dist(ray->ray_dir.x);
		ray->delta_dist.y = compute_delta_dist(ray->ray_dir.y);
		init_step_and_sidedist(player, ray);
		dda_loop(cub, ray, render_map);
		if (BONUS && render_map)
			render_2dray(cub, player, ray);
		else
			render_cubes(cub, player, ray, x);
		x++;
	}
	cub->print_debug_cub = false;
}
