/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_txtr_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:37:47 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/21 23:27:13 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	check_txtr_pxl_bound(t_ray *ray, t_txtr *txtr)
{
	if (txtr->pxl.x < 0)
		txtr->pxl.x = 0;
	if (txtr->pxl.x >= txtr->width)
		txtr->pxl.x = txtr->width - 1;
	if (ray->side == 0 && ray->ray_dir.x < 0)
		txtr->pxl.x = txtr->width - txtr->pxl.x - 1;
	if (ray->side == 1 && ray->ray_dir.y > 0)
		txtr->pxl.x = txtr->width - txtr->pxl.x - 1;
}

/*
txtr_y_coord: represents the current vertical position within the texture
	as a floating-point value. It's used to track which row of the texture
	should be sampled as you iterate through screen pixels.
step: How much to move through the texture for each screen pixel
txtr->pxl.x & txtr->pxl.y are the exact integer pixel coordinates in the texture
 */
void	render_texture(t_cub *cub, t_ray *ray, t_txtr *txtr, int x)
{
	int		y;
	int		color;
	double	step;
	double	txtr_y_coord;
	// double	door_offset;

	txtr->pxl.x = (int)(ray->wall_x * (double)(txtr->width));
	check_txtr_pxl_bound(ray, txtr);
	step = 1.0 * txtr->height / ray->line_height;
	txtr_y_coord = (ray->draw_start - WNDW_H / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		txtr->pxl.y = (int)txtr_y_coord % txtr->height;
		txtr_y_coord += step;
		color = *(int *)(txtr->addr + txtr->pxl.y * txtr->line_len
				+ (txtr->pxl.x * txtr->bpp / 8));
		if (BONUS && FOG)
			color = add_fog(ray->perp_wall_dist, color);
		img_pxl_put(&cub->game_img, x, y, color);
		y++;
	}
}

t_key	get_texture_index(t_cub *cub, t_ray *ray)
{
	if (ray->map.y >= 0 && ray->map.y < (int)cub->map.rows
		&& ray->map.x >= 0 && ray->map.x < (int)ft_strlen(cub->map.grid[ray->map.y]))
	{
		if (cub->map.grid[ray->map.y][ray->map.x] == 'D')
			return (DO);
	}
	if (ray->side == 0)
	{
		if (ray->step.x == 1)
			return (EA);
		else
			return (WE);
	}
	else
	{
		if (ray->step.y == 1)
			return (SO);
		else
			return (NO);
	}
	return (NO);
}
