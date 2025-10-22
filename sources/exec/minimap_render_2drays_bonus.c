/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_2drays_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:23:29 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/22 17:34:43 by tjacquel         ###   ########.fr       */
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
#if MAP_MODE == MAP_CIRCLE
void	draw_pixel_if_valid(t_img *img, int x, int y, int color)
{
	if (is_in_minimap_circle(x, y) && x >= 0 && x < WNDW_W && y >= 0 && y < WNDW_H)
		img_pxl_put(img, x, y, color);
}

#elif MAP_MODE == MAP_VIEWPORT
void	draw_pixel_if_valid(t_cub *cub, int x, int y, int color)
{
	if (x >= MNMAP_MARGIN && x < MNMAP_MARGIN + cub->minimap_width
		&& y >= MNMAP_Y && y < MNMAP_Y + cub->minimap_height)
		img_pxl_put(&(cub->game_img), x, y, color);
}

# elif MAP_MODE == MAP_SCALED
void	draw_pixel_if_valid(t_img *img, int x, int y, int color)
{
	if (x >= MNMAP_X && x < MNMAP_X + MNMAP_W
		&& y >= MNMAP_Y && y < MNMAP_Y + MNMAP_H)
		img_pxl_put(img, x, y, color);
}
#endif

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
		img_pxl_put(&cub->game_img, start.x, start.y, RGB_RAY_YLW);
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
		impact.y = buff->map.y + (buff->step.y == -1);;
		impact.x = player->pos.x + (impact.y - player->pos.y)
			* buff->ray_dir.x / buff->ray_dir.y;
	}
	return (impact);
}

#if MAP_MODE == MAP_SCALED

/*
Boolean arithmetic x = y + (z == 1)
	is equivalent to
	x = y
	if (z == 1)
		x += 1
*/
void	render_2dray(t_cub *cub, t_player *player)
{
	t_vec	impact;
	t_coord	start;
	int		x;
	double	scale;

	scale = get_map_scale(cub);
	x = 0;
	while (x < WNDW_W)
	{
		impact = compute_2dray_impact(&(cub->buff[x]), player);
		start.x = MNMAP_X + (int)(player->pos.x * scale);
		start.y = MNMAP_Y + (int)(player->pos.y * scale);
		impact.x = MNMAP_X + (int)(impact.x * scale);
		impact.y = MNMAP_Y + (int)(impact.y * scale);
		draw_ray_line(cub, start, (t_coord){(int)impact.x, (int)impact.y});
		x++;
	}
}

#elif MAP_MODE == MAP_VIEWPORT
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

#elif MAP_MODE == MAP_CIRCLE

void	render_2dray(t_cub *cub, t_player *player)
{
	t_vec	impact;
	t_coord	start;
	int		x;

	x = 0;
	while (x < WNDW_W)
	{
		start.x = MNMAP_CENTER_X;
		start.y = MNMAP_CENTER_Y;
		impact.x = MNMAP_CENTER_X
			+ (int)((impact.x - player->pos.x) * MNMAP_SCALE);
		impact.y = MNMAP_CENTER_Y
			+ (int)((impact.y - player->pos.y) * MNMAP_SCALE);
		draw_ray_line(cub, start, (t_coord){(int)impact.x, (int)impact.y});
		x++;
	}
}

#else
void	render_2dray(t_cub *cub, t_player *player)
{
	t_vec	impact;
	t_coord	start;
	int		x;

	x = 0;
	while (x < WNDW_W)
	{
		impact = compute_2dray_impact(&(cub->buff[x]), player);
		start.x = MNMAP_MARGIN
			+ (int)((player->pos.x * TILE_SIZE) / MAP_RATIO);
		start.y = MNMAP_MARGIN
			+ (int)((player->pos.y * TILE_SIZE) / MAP_RATIO);
		impact.x = MNMAP_MARGIN
			+ ((impact.x * TILE_SIZE) / MAP_RATIO);
		impact.y = MNMAP_MARGIN
			+ ((impact.y * TILE_SIZE) / MAP_RATIO);
		draw_ray_line(cub, start, (t_coord){(int)impact.x, (int)impact.y});
		x++;
	}
}
#endif