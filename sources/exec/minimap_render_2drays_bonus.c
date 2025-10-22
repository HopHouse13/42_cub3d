/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_2drays_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:23:29 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/22 14:56:47 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#if MAP_MODE == MAP_CIRCLE
bool	ray_outside_minimap(t_cub *cub, t_ray *ray)
{
	int	screen_x;
	int	screen_y;

	// Convert map coordinates to screen pixel coordinates
	screen_x = MINIMAP_CENTER_X + (int)((ray->map.x - cub->player.pos.x) * MINIMAP_SCALE);
	screen_y = MINIMAP_CENTER_Y + (int)((ray->map.y - cub->player.pos.y) * MINIMAP_SCALE);

	// Use the existing circle check
	return !is_in_minimap_circle(screen_x, screen_y);
}

#elif MAP_MODE == MAP_VIEWPORT
bool	ray_outside_minimap(t_cub *cub, t_ray *ray)
{
	t_vec	center;
	t_vec	dist;
	t_vec	max_dist;

	get_map_center(cub, &center);
	dist.x = fabs(ray->map.x - center.x);
	dist.y = fabs(ray->map.y - center.y);
	max_dist.x = MINIMAP_VISIBLE_COLS / 2.0 + 2;
	max_dist.y = MINIMAP_VISIBLE_ROWS / 2.0 + 2;
	if (dist.x > max_dist.x || dist.y > max_dist.y)
		return (true);
	return (false);
}
#endif

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

#else
void	draw_pixel_if_valid(t_img *img, int x, int y, int color)
{
# if MAP_MODE == MAP_VIEWPORT
	if (x >= MINIMAP_X && x < MINIMAP_X + MINIMAP_WIDTH
		&& y >= MINIMAP_Y && y < MINIMAP_Y + MINIMAP_HEIGHT)
		img_pxl_put(img, x, y, color);
	# elif MAP_MODE == MAP_SCALED
	if (x >= MINIMAP_X && x < MINIMAP_X + MINIMAP_WIDTH
		&& y >= MINIMAP_Y && y < MINIMAP_Y + MINIMAP_HEIGHT)
		img_pxl_put(img, x, y, color);
	# else
	if (x >= 0 && x < WNDW_W && y >= 0 && y < WNDW_H)
		img_pxl_put(img, x, y, color);
	# endif
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
/* void	render_2dray(t_cub *cub, t_player *player, t_ray *ray)
{
	t_vec	impact;
	t_coord	start;
	#if MAP_MODE == MAP_VIEWPORT
	// t_coord viewport_offset;
	// viewport_offset = (t_coord){0, 0};
	t_vec	map_center;
	t_coord	minimap_center;
	#endif

	#if MAP_MODE == MAP_SCALED
	double	scale;
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
		impact.y = ray->map.y + (ray->step.y == -1);;
		impact.x = player->pos.x + (impact.y - player->pos.y) * ray->ray_dir.x
			/ ray->ray_dir.y;
	}

	# if MAP_MODE == MAP_CIRCLE
	start.x = MINIMAP_CENTER_X;
	start.y = MINIMAP_CENTER_Y;
	impact.x = MINIMAP_CENTER_X + (int)((impact.x - player->pos.x) * MINIMAP_SCALE);
	impact.y = MINIMAP_CENTER_Y + (int)((impact.y - player->pos.y) * MINIMAP_SCALE);

	# else
		#if MAP_MODE == MAP_VIEWPORT

		// Get the same clamped center as render_map uses
		get_map_center(cub, &map_center);
		minimap_center.x = MINIMAP_MARGIN + MINIMAP_WIDTH / 2;
		minimap_center.y = MINIMAP_MARGIN + MINIMAP_HEIGHT / 2;

		// Transform player position relative to map_center
		start.x = minimap_center.x + (int)((player->pos.x - map_center.x) * MINIMAP_TILE_SIZE);
		start.y = minimap_center.y + (int)((player->pos.y - map_center.y) * MINIMAP_TILE_SIZE);

		// Transform impact point relative to map_center
		impact.x = minimap_center.x + (int)((impact.x - map_center.x) * MINIMAP_TILE_SIZE);
		impact.y = minimap_center.y + (int)((impact.y - map_center.y) * MINIMAP_TILE_SIZE);

		#elif MAP_MODE == MAP_SCALED
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
} */

void	render_2dray(t_cub *cub, t_player *player)
{
	t_vec	impact;
	t_coord	start;
	int		x;
	#if MAP_MODE == MAP_VIEWPORT
	// t_coord viewport_offset;
	// viewport_offset = (t_coord){0, 0};
	t_vec	map_center;
	t_coord	minimap_center;
	#endif

	#if MAP_MODE == MAP_SCALED
	double	scale;
	scale = get_map_scale(cub);
	#endif

	x = 0;
	while (x < WNDW_W)
{
	if (cub->buff[x].side == 0)
	{
		impact.x = cub->buff[x].map.x + (cub->buff[x].step.x == -1);
		impact.y = player->pos.y + (impact.x - player->pos.x) * cub->buff[x].ray_dir.y
			/ cub->buff[x].ray_dir.x;
	}
	else
	{
		impact.y = cub->buff[x].map.y + (cub->buff[x].step.y == -1);;
		impact.x = player->pos.x + (impact.y - player->pos.y) * cub->buff[x].ray_dir.x
			/ cub->buff[x].ray_dir.y;
	}

	# if MAP_MODE == MAP_CIRCLE
	start.x = MINIMAP_CENTER_X;
	start.y = MINIMAP_CENTER_Y;
	impact.x = MINIMAP_CENTER_X + (int)((impact.x - player->pos.x) * MINIMAP_SCALE);
	impact.y = MINIMAP_CENTER_Y + (int)((impact.y - player->pos.y) * MINIMAP_SCALE);

	# else
		#if MAP_MODE == MAP_VIEWPORT

		// Get the same clamped center as render_map uses
		get_map_center(cub, &map_center);
		minimap_center.x = MINIMAP_MARGIN + MINIMAP_WIDTH / 2;
		minimap_center.y = MINIMAP_MARGIN + MINIMAP_HEIGHT / 2;

		// Transform player position relative to map_center
		start.x = minimap_center.x + (int)((player->pos.x - map_center.x) * MINIMAP_TILE_SIZE);
		start.y = minimap_center.y + (int)((player->pos.y - map_center.y) * MINIMAP_TILE_SIZE);

		// Transform impact point relative to map_center
		impact.x = minimap_center.x + (int)((impact.x - map_center.x) * MINIMAP_TILE_SIZE);
		impact.y = minimap_center.y + (int)((impact.y - map_center.y) * MINIMAP_TILE_SIZE);

		#elif MAP_MODE == MAP_SCALED
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
	x++;
}
}
