/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_viewport_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:25:05 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/23 00:46:29 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

#if MAP_MODE == MAP_VIEWPORT

// 1. Calculate offset (top-left corner of viewport in map coordinates)
// 2. Clamp to positive (don't go before start of map) (offset < 0)
static double	clamp_viewport_axis(double player_pos, int visible_tiles,
		int map_size)
{
	double	offset;
	int		half_tiles;

	half_tiles = visible_tiles / 2;
	offset = player_pos - half_tiles;
	if (offset < 0)
		offset = 0;
	if (map_size > visible_tiles)
	{
		if (offset + visible_tiles > map_size)
			offset = map_size - visible_tiles;
	}
	else
		offset = 0;
	return (offset);
}

// 3. Handle X dimension
//		if		Map larger than viewport - clamp to left/right edge
//		else	Map smaller than viewport - center map (offset.x = 0)
// 4. Handle Y dimension
//		if		Map larger than viewport - clamp to top/bottom edge
//		else	Map smaller than viewport - center map (offset.y = 0)
// 5. Center is offset + half viewport (middle of visible area)
void	get_map_center(t_cub *cub, t_vec *map_center)
{
	int		half_cols;
	int		half_rows;
	t_vec	offset;

	half_cols = MNMAP_COLS / 2;
	half_rows = MNMAP_ROWS / 2;
	offset.x = clamp_viewport_axis(cub->player.pos.x, MNMAP_COLS,
			(int)cub->map.max_col);
	offset.y = clamp_viewport_axis(cub->player.pos.y, MNMAP_ROWS,
			(int)cub->map.rows);
	map_center->x = offset.x + half_cols;
	map_center->y = offset.y + half_rows;
}

/* Convert screen pixel to map coordinates relative to player */
// 1. Center of the rectangular minimap
// 2. Convert screen position to relative offset from center
// 3. Add center position (which may be clamped) to get map coordinates
static void	screen_to_map_coords(t_cub *cub, t_coord pxl, t_vec map_center,
	t_vec *map_pos)
{
	t_vec	tile_offset;
	t_coord	minimap_center;

	minimap_center.x = MNMAP_MARGIN + cub->minimap_width / 2;
	minimap_center.y = MNMAP_MARGIN + cub->minimap_height / 2;
	tile_offset.x = (pxl.x - minimap_center.x) / (float)MNMAP_TILE_SIZE;
	tile_offset.y = (pxl.y - minimap_center.y) / (float)MNMAP_TILE_SIZE;
	map_pos->x = map_center.x + tile_offset.x;
	map_pos->y = map_center.y + tile_offset.y;
}

/*	t_vec	map_pos;	// Fractional map coordinates (e.g., 35.73, 16.42)
	t_coord	map_tile;	// INTEGER tile indices for grid lookup (e.g., [16][35])
	t_coord	tile_pxl;	// Pixel position WITHIN a tile
							(e.g., 11 pixels from left edge)
*/
static void	draw_minimap_pixel(t_cub *cub, int x, int y, t_vec map_center)
{
	t_vec	map_pos;
	t_coord	map_tile;
	t_coord	tile_pxl;
	int		color;

	screen_to_map_coords(cub, (t_coord){x, y}, map_center, &map_pos);
	map_tile.x = (int)floor(map_pos.x);
	map_tile.y = (int)floor(map_pos.y);
	if (map_tile.y < 0 || map_tile.y >= (int)cub->map.rows)
		return ;
	if (map_tile.x < 0
		|| map_tile.x >= (int)ft_strlen(cub->map.grid[map_tile.y]))
		return ;
	if (cub->map.grid[map_tile.y][map_tile.x] == 'D')
		color = minimap_door_color(cub, map_tile.x, map_tile.y);
	else
		color = char_to_tile_rgb(cub->map.grid[map_tile.y][map_tile.x]);
	tile_pxl.x = (int)((map_pos.x - floor(map_pos.x)) * MNMAP_TILE_SIZE);
	tile_pxl.y = (int)((map_pos.y - floor(map_pos.y)) * MNMAP_TILE_SIZE);
	if (MNMAP_TILE_SIZE >= 8
		&& (tile_pxl.x == 0 || tile_pxl.x == MNMAP_TILE_SIZE - 1
			|| tile_pxl.y == 0 || tile_pxl.y == MNMAP_TILE_SIZE - 1))
		color = DARK_GREY;
	img_pxl_put(&cub->game_img, x, y, color);
}

void	render_map(t_cub *cub)
{
	t_vec	map_center;
	int		x;
	int		y;

	get_map_center(cub, &map_center);
	y = MNMAP_MARGIN;
	while (y < MNMAP_MARGIN + cub->minimap_height)
	{
		x = MNMAP_MARGIN;
		while (x < MNMAP_MARGIN + cub->minimap_width)
		{
			draw_minimap_pixel(cub, x, y, map_center);
			x++;
		}
		y++;
	}
}

#endif