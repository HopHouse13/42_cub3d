/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_bonus3_scaled.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:20:15 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/20 16:09:11 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

# if MAP_MODE == MAP_SCALED
/* Get the smaller scale to ensure entire map fits */
float	get_map_scale(t_cub *cub)
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

static void	fill_tile_pxl_range(t_cub *cub, t_coord pxl_start, t_coord pxl_end, int x, int y)
{
	t_coord pxl;

	pxl.y = pxl_start.y;
	while (pxl.y < pxl_end.y)
	{
		pxl.x = pxl_start.x;
		while (pxl.x < pxl_end.x)
		{
			if ((pxl_end.x - pxl_start.x) >= 8 &&
				(pxl.y == pxl_start.y || pxl.y == pxl_end.y - 1 ||
				pxl.x == pxl_start.x || pxl.x == pxl_end.x - 1))
				draw_pixel_if_valid(&cub->game_img, pxl.x, pxl.y, 0x000000);
			else
				draw_pixel_if_valid(&cub->game_img, pxl.x, pxl.y,
					char_to_tile_rgb(cub->map.grid[y][x]));
			pxl.x++;
		}
		pxl.y++;
	}
}
#endif

#if MAP_MODE != MAP_VIEWPORT && MAP_MODE != MAP_CIRCLE
void	render_map(t_cub *cub)
{
	size_t	x;
	size_t	y;
	size_t	row_len;
	#if MAP_MODE == MAP_SCALED
	float	scale;
	int		tile_size;
	t_coord	pxl_start;
	t_coord	pxl_end;


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
	while (y < cub->map.rows && y < WNDW_H)
	{
		#if MAP_MODE == MAP_SCALED
		pxl_start.y = MINIMAP_Y + (int)(y * scale);
		pxl_end.y = MINIMAP_Y + (int)((y + 1) * scale);
		#endif

		x = 0;
		row_len = ft_strlen(cub->map.grid[y]);
		while (x < row_len && x < WNDW_W)
		{
			#if MAP_MODE == MAP_SCALED
			pxl_start.x = MINIMAP_X + (int)(x * scale);
			pxl_end.x = MINIMAP_X + (int)((x + 1) * scale);

			// Fill the entire pixel range for this tile
			fill_tile_pxl_range(cub, pxl_start, pxl_end, x, y);
			// if (tile_size == 1)
			// 	draw_pixel_if_valid(&cub->game_img, pxl_start.x, pxl_start.y, char_to_tile_rgb(cub->map.grid[y][x]));
			// else
			// 	render_sqr(&cub->game_img, (t_sqr){
			// 	pxl_start.x, pxl_start.y,
			// 	tile_size,
			// 	char_to_tile_rgb(cub->map.grid[y][x])});
			# else
			render_sqr(&cub->game_img, (t_sqr){10 + x * TILE_SIZE / MAP_RATIO,
				10 + y * TILE_SIZE / MAP_RATIO, TILE_SIZE / MAP_RATIO, char_to_tile_rgb(cub->map.grid[y][x])});
			# endif
			x++;
		}
		y++;
	}
}
#endif