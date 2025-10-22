/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_scaled_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:20:15 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/23 00:46:29 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

#if MAP_MODE == MAP_SCALED
/* Get the smaller scale to ensure entire map fits */
	// Ensure minimum 1 pixel per tile (map won't exceed boundaries)
	// This effectively caps the map size that can be displayed
	// Use smaller scale so map fits in both dimensions
double	get_map_scale(t_cub *cub)
{
	t_vec	scale;
	double	scale_res;

	scale.x = (double)cub->minimap_width / (double)cub->map.max_col;
	scale.y = (double)cub->minimap_height / (double)cub->map.rows;
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
	int		color;

	if (cub->map.grid[y][x] == 'D')
		color = minimap_door_color(cub, x, y);
	else
		color = char_to_tile_rgb(cub->map.grid[y][x]);
	pixel.y = pxl.start.y;
	while (pixel.y < pxl.end.y)
	{
		pixel.x = pxl.start.x;
		while (pixel.x < pxl.end.x)
		{
			if ((pxl.end.x - pxl.start.x) >= 8
				&& (pixel.y == pxl.start.y || pixel.y == pxl.end.y - 1
					|| pixel.x == pxl.start.x || pixel.x == pxl.end.x - 1))
				draw_pixel_if_valid(cub, pixel.x, pixel.y, DARK_GREY);
			else
				draw_pixel_if_valid(cub, pixel.x, pixel.y, color);
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
		pxl.start.y = MNMAP_MARGIN + (int)(y * scale);
		pxl.end.y = MNMAP_MARGIN + (int)((y + 1) * scale);
		x = 0;
		row_len = ft_strlen(cub->map.grid[y]);
		while (x < row_len && x < WNDW_W)
		{
			pxl.start.x = MNMAP_MARGIN + (int)(x * scale);
			pxl.end.x = MNMAP_MARGIN + (int)((x + 1) * scale);
			fill_tile_pxl_range(cub, pxl, x, y);
			x++;
		}
		y++;
	}
}

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
		start.x = MNMAP_MARGIN + (int)(player->pos.x * scale);
		start.y = MNMAP_MARGIN + (int)(player->pos.y * scale);
		impact.x = MNMAP_MARGIN + (int)(impact.x * scale);
		impact.y = MNMAP_MARGIN + (int)(impact.y * scale);
		draw_ray_line(cub, start, (t_coord){(int)impact.x, (int)impact.y});
		x++;
	}
}
#endif
