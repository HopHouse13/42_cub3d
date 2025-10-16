/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:25:05 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/16 22:14:54 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Boolean arithmetic instead of if/else */
static void	init_bresenham(t_coord start, t_coord end, t_coord *delta,
		t_coord *step)
{
	delta->x = abs(end.x - start.x);
	delta->y = abs(end.y - start.y);
	step->x = 1 - 2 * (start.x >= end.x);
	step->y = 1 - 2 * (start.y >= end.y);
}

static void	draw_pixel_if_valid(t_cub *cub, int x, int y)
{
	if (x >= 0 && x <= cub->window_width && y >= 0 && y <= cub->window_height)
		img_pxl_put(&cub->map_img, x, y, 0xFFFF00);
}

/* Bresenham's line algorithm
Core idea : draw a straight line from point A to point B on a pixel grid (INT)
The Decision Variable (err) tracks: "Am I above or below the ideal line?"
*/
static void	draw_ray_line(t_cub *cub, t_coord start, t_coord end)
{
	t_coord	delta;
	t_coord	step;
	int		err;
	int		err2;

	init_bresenham(start, end, &delta, &step);
	err = delta.x - delta.y;
	while (1)
	{
		draw_pixel_if_valid(cub, start.x, start.y);
		if (start.x == end.x && start.y == end.y)
			break ;
		err2 = 2 * err;
		if (err2 > -delta.y)
		{
			err -= delta.y;
			start.x += step.x;
		}
		if (err2 < delta.x)
		{
			err += delta.x;
			start.y += step.y;
		}
	}
}

/*
Boolean arithmetic x = y + (z == 1)
	is equivalent to
	x = y
	if (z == 1)
		x += 1
*/
void	render_2dray(t_cub *cub, t_player *player, t_ray *ray)
{
	t_vec	impact;
	t_coord	start;

	if (ray->side == 1)
	{
		impact.x = ray->map.x + (ray->step.x == -1);
		impact.y = player->pos.y + (impact.x - player->pos.x) * ray->ray_dir.y
			/ ray->ray_dir.x;
	}
	else
	{
		impact.y = ray->map.y + (ray->step.y == -1);
		impact.x = player->pos.x + (impact.y - player->pos.y) * ray->ray_dir.x
			/ ray->ray_dir.y;
	}
	start.x = (int)((player->pos.x * TILE_SIZE) / MAP_RATIO);
	start.y = (int)((player->pos.y * TILE_SIZE) / MAP_RATIO);
	impact.x = ((impact.x * TILE_SIZE) / MAP_RATIO);
	impact.y = ((impact.y * TILE_SIZE) / MAP_RATIO);
	draw_ray_line(cub, start, (t_coord){(int)impact.x, (int)impact.y});
}

void	render_map(t_cub *cub)
{
	size_t	x;
	size_t	y;
	size_t	row_len;

	y = 0;
	while (y < cub->map.rows)
	{
		x = 0;
		row_len = ft_strlen(cub->map.grid[y]);
		while (x < row_len)
		{
			if (char_to_tile(cub->map.grid[y][x]) == TILE_WALL)
				render_sqr(&cub->map_img, (t_sqr){x * TILE_SIZE / MAP_RATIO, y
					* TILE_SIZE / MAP_RATIO, TILE_SIZE / MAP_RATIO, RGB_RED});
			else
				render_sqr(&cub->map_img, (t_sqr){x * TILE_SIZE / MAP_RATIO, y
					* TILE_SIZE / MAP_RATIO, TILE_SIZE / MAP_RATIO, RGB_FLOOR});
			x++;
		}
		y++;
	}
}
