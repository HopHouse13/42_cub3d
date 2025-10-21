/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_scaled_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:20:15 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/20 18:09:40 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#if MAP_MODE == MAP_SCALED
/* Get the smaller scale to ensure entire map fits */
	// Ensure minimum 1 pixel per tile (map won't exceed boundaries)
	// This effectively caps the map size that can be displayed
	// Use smaller scale so map fits in both dimensions
double	get_map_scale(t_cub *cub)
{
	t_vec	scale;
	double	scale_res;

	scale.x = (double)MINIMAP_WIDTH / (double)cub->map.max_col;
	scale.y = (double)MINIMAP_HEIGHT / (double)cub->map.rows;
	if (scale.x < scale.y)
		scale_res = scale.x;
	else
		scale_res = scale.y;
	if (scale_res < 1.0)
		scale_res = 1.0;
	return (scale_res);
}

// Fill the entire pixel range for this tile
static void	fill_tile_pxl_range(t_cub *cub, t_pxl_range pxl, int x, int y)
{
	t_coord	pixel;

	pixel.y = pxl.start.y;
	while (pixel.y < pxl.end.y)
	{
		pixel.x = pxl.start.x;
		while (pixel.x < pxl.end.x)
		{
			if ((pxl.end.x - pxl.start.x) >= 8
				&& (pixel.y == pxl.start.y || pixel.y == pxl.end.y - 1
					|| pixel.x == pxl.start.x || pixel.x == pxl.end.x - 1))
				draw_pixel_if_valid(&cub->game_img, pixel.x, pixel.y, 0x000000);
			else
				draw_pixel_if_valid(&cub->game_img, pixel.x, pixel.y,
					char_to_tile_rgb(cub->map.grid[y][x]));
			pixel.x++;
		}
		pixel.y++;
	}
}

void	render_map(t_cub *cub)
{
	size_t		x;
	size_t		y;
	size_t		row_len;
	double		scale;
	t_pxl_range	pxl;

	scale = get_map_scale(cub);
	y = 0;
	while (y < cub->map.rows && y < WNDW_H)
	{
		pxl.start.y = MINIMAP_Y + (int)(y * scale);
		pxl.end.y = MINIMAP_Y + (int)((y + 1) * scale);
		x = 0;
		row_len = ft_strlen(cub->map.grid[y]);
		while (x < row_len && x < WNDW_W)
		{
			pxl.start.x = MINIMAP_X + (int)(x * scale);
			pxl.end.x = MINIMAP_X + (int)((x + 1) * scale);
			fill_tile_pxl_range(cub, pxl, x, y);
			x++;
		}
		y++;
	}
}
#endif

#if MAP_MODE != MAP_VIEWPORT && MAP_MODE != MAP_CIRCLE && MAP_MODE != MAP_SCALED

void	render_map(t_cub *cub)
{
	size_t	x;
	size_t	y;
	size_t	row_len;

	y = 0;
	while (y < cub->map.rows && y < WNDW_H)
	{
		x = 0;
		row_len = ft_strlen(cub->map.grid[y]);
		while (x < row_len && x < WNDW_W)
		{
			render_sqr(&cub->game_img, (t_sqr){10 + x * TILE_SIZE / MAP_RATIO,
				10 + y * TILE_SIZE / MAP_RATIO, TILE_SIZE / MAP_RATIO,
				char_to_tile_rgb(cub->map.grid[y][x])});
			x++;
		}
		y++;
	}
}

#endif
