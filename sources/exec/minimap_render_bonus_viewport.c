/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_bonus_viewport.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:25:05 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/20 01:23:26 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


#if MAP_VIEWPORT

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
void	get_minimap_center(t_cub *cub, t_vec *center)
{
	int		half_cols;
	int		half_rows;
	t_vec	offset;

	half_cols = MINIMAP_VISIBLE_COLS / 2;
	half_rows = MINIMAP_VISIBLE_ROWS / 2;
	offset.x = clamp_viewport_axis(cub->player.pos.x, MINIMAP_VISIBLE_COLS,
		(int)cub->map.max_col);
	offset.y = clamp_viewport_axis(cub->player.pos.y, MINIMAP_VISIBLE_ROWS,
		(int)cub->map.rows);
	center->x = offset.x + half_cols;
	center->y = offset.y + half_rows;
}

/* Convert screen pixel to map coordinates relative to player */
static void	screen_to_map_coords(int x, int y, t_vec center,
		t_vec *map_coords)
{
	t_vec	relative;
	int		center_screen_x;
	int		center_screen_y;

	// Center of the rectangular minimap
	center_screen_x = MINIMAP_MARGIN + MINIMAP_WIDTH / 2;
	center_screen_y = MINIMAP_MARGIN + MINIMAP_HEIGHT / 2;

	// Convert screen position to relative offset from center
	relative.x = (x - center_screen_x) / (float)MINIMAP_TILE_SIZE;
	relative.y = (y - center_screen_y) / (float)MINIMAP_TILE_SIZE;

	// Add center position (which may be clamped) to get map coordinates
	map_coords->x = center.x + relative.x;
	map_coords->y = center.y + relative.y;
}

static void	draw_minimap_pixel(t_cub *cub, int x, int y, t_vec center)
{
	t_vec	map_pos;
	t_coord	map;
	t_coord	tile;
	int		color;

	screen_to_map_coords(x, y, center, &map_pos);
	map.x = (int)floor(map_pos.x);
	map.y = (int)floor(map_pos.y);

	if (map.y < 0 || map.y >= (int)cub->map.rows)
		return;
	if (map.x < 0 || map.x >= (int)ft_strlen(cub->map.grid[map.y]))
		return;
	color = char_to_tile_rgb(cub->map.grid[map.y][map.x]);
	tile.x = (int)((map_pos.x - floor(map_pos.x)) * MINIMAP_TILE_SIZE);
	tile.y = (int)((map_pos.y - floor(map_pos.y)) * MINIMAP_TILE_SIZE);
	if (MINIMAP_TILE_SIZE >= 8 &&
		(tile.x == 0 || tile.x == MINIMAP_TILE_SIZE - 1 ||
		tile.y == 0 || tile.y == MINIMAP_TILE_SIZE - 1))
		color = 0x000000;

	img_pxl_put(&cub->game_img, x, y, color);
}

void render_map(t_cub *cub)
{
	t_vec	center;
	int		x;
	int		y;

	get_minimap_center(cub, &center);

	y = MINIMAP_Y;
	while (y < MINIMAP_Y + MINIMAP_HEIGHT)
	{
		x = MINIMAP_MARGIN;
		while (x < MINIMAP_MARGIN + MINIMAP_WIDTH)
		{
			draw_minimap_pixel(cub, x, y, center);
			x++;
		}
		y++;
	}
}


# endif