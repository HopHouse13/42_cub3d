/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_2drays_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:23:29 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/23 00:46:29 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

/* Boolean arithmetic instead of if/else */
static void	init_bresenham(t_coord start, t_coord end, t_coord *delta,
		t_coord *step)
{
	delta->x = abs(end.x - start.x);
	delta->y = abs(end.y - start.y);
	step->x = 1 - 2 * (start.x >= end.x);
	step->y = 1 - 2 * (start.y >= end.y);
}

// #if MAP_MODE == MAP_VIEWPORT

void	draw_pixel_if_valid(t_cub *cub, int x, int y, int color)
{
	if (x >= MNMAP_MARGIN && x < MNMAP_MARGIN + cub->minimap_width
		&& y >= MNMAP_MARGIN && y < MNMAP_MARGIN + cub->minimap_height)
		img_pxl_put(&(cub->game_img), x, y, color);
}

// #endif

/* Bresenham's line algorithm
Core idea : draw a straight line from point A to point B on a pixel grid (INT)
The Decision Variable (err) tracks: "Am I above or below the ideal line?"
*/
void	draw_ray_line(t_cub *cub, t_coord start, t_coord end)
{
	t_coord	delta;
	t_coord	step;
	int		err;
	int		err2;

	init_bresenham(start, end, &delta, &step);
	err = delta.x - delta.y;
	while (1)
	{
		draw_pixel_if_valid(cub, start.x, start.y, RGB_RAY_YLW);
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

t_vec	compute_2dray_impact(t_ray_buffer *buff, t_player *player)
{
	t_vec	impact;

	if (buff->side == 0)
	{
		impact.x = buff->map.x + (buff->step.x == -1);
		impact.y = player->pos.y + (impact.x - player->pos.x)
			* buff->ray_dir.y / buff->ray_dir.x;
	}
	else
	{
		impact.y = buff->map.y + (buff->step.y == -1);
		impact.x = player->pos.x + (impact.y - player->pos.y)
			* buff->ray_dir.x / buff->ray_dir.y;
	}
	return (impact);
}

#if MAP_MODE == MAP_VIEWPORT

// Get the same clamped center as render_map uses
// Transform player position relative to minimap_center
// Transform impact point relative to minimap_center
void	render_2dray(t_cub *cub, t_player *player)
{
	t_vec	impact;
	t_vec	map_center;
	t_coord	minimap_center;
	t_coord	start;
	int		x;

	x = 0;
	while (x < WNDW_W)
	{
		impact = compute_2dray_impact(&(cub->buff[x]), player);
		get_map_center(cub, &map_center);
		minimap_center.x = MNMAP_MARGIN + cub->minimap_width / 2;
		minimap_center.y = MNMAP_MARGIN + cub->minimap_height / 2;
		start.x = minimap_center.x
			+ (int)((player->pos.x - map_center.x) * MNMAP_TILE_SIZE);
		start.y = minimap_center.y
			+ (int)((player->pos.y - map_center.y) * MNMAP_TILE_SIZE);
		impact.x = minimap_center.x
			+ (int)((impact.x - map_center.x) * MNMAP_TILE_SIZE);
		impact.y = minimap_center.y
			+ (int)((impact.y - map_center.y) * MNMAP_TILE_SIZE);
		draw_ray_line(cub, start, (t_coord){(int)impact.x, (int)impact.y});
		x++;
	}
}

#endif
