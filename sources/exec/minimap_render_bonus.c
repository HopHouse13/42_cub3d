/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:25:05 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/18 21:24:13 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define CIRCLE 0
#define SCALED 1


# if SCALED
/* Get the smaller scale to ensure entire map fits */
static float	get_map_scale(t_cub *cub)
{
	float	scale_x;
	float	scale_y;
	float	scale;

	scale_x = (float)MINIMAP_WIDTH / (float)cub->map.max_col;
	scale_y = (float)MINIMAP_HEIGHT / (float)cub->map.rows;

	// Use smaller scale so map fits in both dimensions
	scale = (scale_x < scale_y) ? scale_x : scale_y;

	// Ensure minimum 1 pixel per tile (map won't exceed boundaries)
	// This effectively caps the map size that can be displayed
	if (scale < 1.0)
		scale = 1.0;

	return (scale);
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

void	draw_pixel_if_valid(t_cub *cub, int x, int y, int color)
{
	# if CIRCLE
	if (is_in_minimap_circle(x, y) && x >= 0 && x < WNDW_W && y >= 0 && y < WNDW_H)
		img_pxl_put(&cub->game_img, x, y, color);

	# else
	# if SCALED
	if (x >= MINIMAP_X && x < MINIMAP_X + MINIMAP_WIDTH
		&& y >= MINIMAP_Y && y < MINIMAP_Y + MINIMAP_HEIGHT)
		img_pxl_put(&cub->game_img, x, y, color);
	# else
	if (x >= 0 && x < WNDW_W && y >= 0 && y < WNDW_H)
		img_pxl_put(&cub->game_img, x, y, color);
	# endif
	# endif
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

	#if SCALED
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

	# if CIRCLE
	start.x = MINIMAP_CENTER_X;
	start.y = MINIMAP_CENTER_Y;
	impact.x = MINIMAP_CENTER_X + (int)((impact.x - player->pos.x) * MINIMAP_SCALE);
	impact.y = MINIMAP_CENTER_Y + (int)((impact.y - player->pos.y) * MINIMAP_SCALED);

	# else
	#if SCALED
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
# if CIRCLE
/* Render the circular minimap centered on player */
void	render_map(t_cub *cub)
{
	int	x;
	int	y;

	y = MINIMAP_CENTER_Y - MINIMAP_RADIUS;
	while (y <= MINIMAP_CENTER_Y + MINIMAP_RADIUS)
	{
		x = MINIMAP_CENTER_X - MINIMAP_RADIUS;
		while (x <= MINIMAP_CENTER_X + MINIMAP_RADIUS)
		{
			if (is_in_minimap_circle(x, y))
				draw_minimap_pixel(cub, x, y);
			x++;
		}
		y++;
	}
	// draw_player_indicator(cub);
	// draw_direction_line(cub, &cub->player);
}
# else
void	render_map(t_cub *cub)
{
	size_t	x;
	size_t	y;
	size_t	row_len;
	#if SCALED
	float	scale;
	int		tile_size;
	int		pixel_x;
	int		pixel_y;

	// if (cub->map.max_col > cub->map.rows)
	// 	tile_size = MINIMAP_WIDTH / cub->map.max_col;
	// else
	// 	tile_size = MINIMAP_HEIGHT / cub->map.rows;

	scale = get_map_scale(cub);
	tile_size = (int)scale;
	if (tile_size < 1)
		tile_size = 1;
	#endif

	y = 0;
	while (y < cub->map.rows)
	{
		#if SCALED
		pixel_y = MINIMAP_Y + (int)(y * scale);
		// if (pixel_y >= MINIMAP_Y + MINIMAP_HEIGHT)
		// 	break;  // Stop if beyond minimap
		#endif

		x = 0;
		row_len = ft_strlen(cub->map.grid[y]);
		while (x < row_len)
		{
			#if SCALED
			pixel_x = MINIMAP_X + (int)(x * scale);
			// if (pixel_x >= MINIMAP_X + MINIMAP_WIDTH)
			// 	break;  // Stop row if beyond minimap
			// if (pixel_x + tile_size <= MINIMAP_X + MINIMAP_WIDTH
			// 	&& pixel_y + tile_size <= MINIMAP_Y + MINIMAP_HEIGHT)
				render_sqr(&cub->game_img, (t_sqr){
				pixel_x, pixel_y,
				tile_size,
				char_to_tile_rgb(cub->map.grid[y][x])});
			# else
			render_sqr(&cub->game_img, (t_sqr){10 + x * TILE_SIZE / MAP_RATIO,
				10 + y * TILE_SIZE / MAP_RATIO, TILE_SIZE / MAP_RATIO, char_to_tile_rgb(cub->map.grid[y][x])});
			# endif
			x++;
		}
		y++;
	}
}

# endif


// void	draw_line(t_img *img, t_line line, int res_width)
// {
// 	int		i;
// 	int		x;
// 	int		y;
// 	double	dir_x;
// 	double	dir_y;

// 	dir_x = cos(line.dir);
// 	dir_y = sin(line.dir);
// 	i = -1;
// 	while (++i <= line.size)
// 	{
// 		x = dir_x * i + line.x;
// 		y = dir_y * i + line.y;
// 		img->addr[x + y * res_width] = line.color;
// 	}
// }