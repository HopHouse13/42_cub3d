/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_2drays_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:23:29 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/19 23:54:04 by tjacquel         ###   ########.fr       */
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

void	draw_pixel_if_valid(t_img *img, int x, int y, int color)
{
	#if MAP_CIRCLE
	if (is_in_minimap_circle(x, y) && x >= 0 && x < WNDW_W && y >= 0 && y < WNDW_H)
		img_pxl_put(img, x, y, color);

	#else
	# if MAP_VIEWPORT
	if (x >= MINIMAP_X && x < MINIMAP_X + MINIMAP_WIDTH
		&& y >= MINIMAP_Y && y < MINIMAP_Y + MINIMAP_HEIGHT)
		img_pxl_put(img, x, y, color);
	# elif MAP_SCALED
	if (x >= MINIMAP_X && x < MINIMAP_X + MINIMAP_WIDTH
		&& y >= MINIMAP_Y && y < MINIMAP_Y + MINIMAP_HEIGHT)
		img_pxl_put(img, x, y, color);
	# else
	if (x >= 0 && x < WNDW_W && y >= 0 && y < WNDW_H)
		img_pxl_put(img, x, y, color);
	# endif
	#endif
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
		draw_pixel_if_valid(&cub->game_img, start.x, start.y, RGB_RAY_YLW);
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
	#if MAP_VIEWPORT
	// t_coord viewport_offset;
	// viewport_offset = (t_coord){0, 0};
	t_vec center;
	int center_screen_x;
	int center_screen_y;
	#endif

	#if MAP_SCALED && !MAP_VIEWPORT
	float scale;
	scale = get_map_scale(cub);
	#endif

	if (ray->side == 0)
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

	# if MAP_CIRCLE
	start.x = MINIMAP_CENTER_X;
	start.y = MINIMAP_CENTER_Y;
	impact.x = MINIMAP_CENTER_X + (int)((impact.x - player->pos.x) * MINIMAP_SCALE);
	impact.y = MINIMAP_CENTER_Y + (int)((impact.y - player->pos.y) * MINIMAP_SCALE);

	# else
		#if MAP_VIEWPORT
		// get_viewport_offset(cub, &viewport_offset);
		// // Transform player position to screen space
		// start.x = MINIMAP_X + (int)((player->pos.x - viewport_offset.x) * MINIMAP_TILE_SIZE);
		// start.y = MINIMAP_Y + (int)((player->pos.y - viewport_offset.y) * MINIMAP_TILE_SIZE);
		// // Transform impact point to screen space
		// impact.x = MINIMAP_X + (int)((impact.x - viewport_offset.x) * MINIMAP_TILE_SIZE);
		// impact.y = MINIMAP_Y + (int)((impact.y - viewport_offset.y) * MINIMAP_TILE_SIZE);

		// Get the same clamped center as render_map uses
		get_minimap_center(cub, &center);
		center_screen_x = MINIMAP_MARGIN + MINIMAP_WIDTH / 2;
		center_screen_y = MINIMAP_MARGIN + MINIMAP_HEIGHT / 2;

		// Transform player position relative to center
		start.x = center_screen_x + (int)((player->pos.x - center.x) * MINIMAP_TILE_SIZE);
		start.y = center_screen_y + (int)((player->pos.y - center.y) * MINIMAP_TILE_SIZE);

		// Transform impact point relative to center
		impact.x = center_screen_x + (int)((impact.x - center.x) * MINIMAP_TILE_SIZE);
		impact.y = center_screen_y + (int)((impact.y - center.y) * MINIMAP_TILE_SIZE);

		#elif MAP_SCALED
		start.x = MINIMAP_X + (int)(player->pos.x * scale);
		start.y = MINIMAP_Y + (int)(player->pos.y * scale);
		impact.x = MINIMAP_X + (int)(impact.x * scale);
		impact.y = MINIMAP_Y + (int)(impact.y * scale);
		#else
		start.x = 10 + (int)((player->pos.x * TILE_SIZE) / MAP_RATIO);
		start.y = 10 + (int)((player->pos.y * TILE_SIZE) / MAP_RATIO);
		impact.x = 10 + ((impact.x * TILE_SIZE) / MAP_RATIO);
		impact.y = 10 + ((impact.y * TILE_SIZE) / MAP_RATIO);
		#endif
	# endif

	draw_ray_line(cub, start, (t_coord){(int)impact.x, (int)impact.y});
}
