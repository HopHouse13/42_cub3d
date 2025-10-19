/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_bonus_viewport.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:25:05 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/20 00:17:36 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


#if MAP_VIEWPORT

/* void	get_minimap_center(t_cub *cub, t_vec *center)
{
	float	half_view_x;
	float	half_view_y;

	// How many tiles fit in half the minimap
	half_view_x = MINIMAP_VISIBLE_COLS / 2.0f;
	half_view_y = MINIMAP_VISIBLE_ROWS / 2.0f;


	// Start with player position as center
	center->x = cub->player.pos.x;
	center->y = cub->player.pos.y;

	// Clamp X - if map is small or player near edges
	if (cub->map.max_col <= MINIMAP_VISIBLE_COLS)
	{
		// Map smaller than viewport - center the map itself
		center->x = cub->map.max_col / 2.0f;
	}
	else
	{
		// Map larger than viewport - clamp to edges
		if (center->x < half_view_x)
			center->x = half_view_x;
		else if (center->x > cub->map.max_col - half_view_x)
			center->x = cub->map.max_col - half_view_x;
	}

	// Clamp Y
	if (cub->map.rows <= MINIMAP_VISIBLE_ROWS)
	{
		// Map smaller than viewport - center the map itself
		center->y = cub->map.rows / 2.0f;
	}
	else
	{
		// Map larger than viewport - clamp to edges
		if (center->y < half_view_y)
			center->y = half_view_y;
		else if (center->y > cub->map.rows - half_view_y)
			center->y = cub->map.rows - half_view_y;
	}
} */

void	get_minimap_center(t_cub *cub, t_vec *center)
{
	int		half_cols;
	int		half_rows;
	float	offset_x;
	float	offset_y;

	half_cols = MINIMAP_VISIBLE_COLS / 2;
	half_rows = MINIMAP_VISIBLE_ROWS / 2;

	// Calculate offset (top-left corner of viewport in map coordinates)
	offset_x = cub->player.pos.x - half_cols;
	offset_y = cub->player.pos.y - half_rows;

	// Clamp to positive (don't go before start of map)
	if (offset_x < 0)
		offset_x = 0;
	if (offset_y < 0)
		offset_y = 0;

	// Handle X dimension
	if ((int)cub->map.max_col > MINIMAP_VISIBLE_COLS)
	{
		// Map larger than viewport - clamp to right edge
		if (offset_x + MINIMAP_VISIBLE_COLS > (int)cub->map.max_col)
			offset_x = cub->map.max_col - MINIMAP_VISIBLE_COLS;
	}
	else
	{
		// Map smaller than viewport - pin to top-left (offset = 0)
		offset_x = 0;
	}

	// Handle Y dimension
	if ((int)cub->map.rows > MINIMAP_VISIBLE_ROWS)
	{
		// Map larger than viewport - clamp to bottom edge
		if (offset_y + MINIMAP_VISIBLE_ROWS > (int)cub->map.rows)
			offset_y = cub->map.rows - MINIMAP_VISIBLE_ROWS;
	}
	else
	{
		// Map smaller than viewport - pin to top-left (offset = 0)
		offset_y = 0;
	}

	// Center is offset + half viewport (middle of visible area)
	center->x = offset_x + half_cols;
	center->y = offset_y + half_rows;
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

	// Draw black border if at edge of tile
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