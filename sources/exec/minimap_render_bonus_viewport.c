/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_bonus_viewport.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:25:05 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/19 23:06:51 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


#if MAP_VIEWPORT

static bool	is_in_minimap(int x, int y)
{
	return (x >= MINIMAP_X && x < MINIMAP_X + MINIMAP_WIDTH
		&& y >= MINIMAP_Y && y < MINIMAP_Y + MINIMAP_HEIGHT);
}

void	get_minimap_center(t_cub *cub, t_vec *center)
{
	float	half_view_x;
	float	half_view_y;

	// How many tiles fit in half the minimap
	half_view_x = (MINIMAP_WIDTH / 2.0f) / MINIMAP_SCALE;
	half_view_y = (MINIMAP_HEIGHT / 2.0f) / MINIMAP_SCALE;

	// Start with player position as center
	center->x = cub->player.pos.x;
	center->y = cub->player.pos.y;

	// Clamp X if map is smaller than viewport or player near edges
	if ((int)cub->map.max_col <= (int)(half_view_x * 2))
	{
		// Map smaller than viewport - center the map
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

	// Clamp Y if map is smaller than viewport or player near edges
	if ((int)cub->map.rows <= (int)(half_view_y * 2))
	{
		// Map smaller than viewport - center the map
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
}

/* Convert screen pixel to map coordinates relative to player */
static void	screen_to_map_coords(int screen_x, int screen_y, t_vec center,
		t_vec *map_coords)
{
	float	rel_x;
	float	rel_y;
	int		center_screen_x;
	int		center_screen_y;

	// Center of the rectangular minimap
	center_screen_x = MINIMAP_X + MINIMAP_WIDTH / 2;
	center_screen_y = MINIMAP_Y + MINIMAP_HEIGHT / 2;

	// Convert screen position to relative offset from center
	rel_x = (screen_x - center_screen_x) / (float)MINIMAP_SCALE;
	rel_y = (screen_y - center_screen_y) / (float)MINIMAP_SCALE;

	// Add center position (which may be clamped) to get map coordinates
	map_coords->x = center.x + rel_x;
	map_coords->y = center.y + rel_y;
}

// /* Calculate which tile is at the center of the minimap */
// static void screen_to_viewport_coords(t_coord screen, t_coord viewport_offset, t_vec *map_pos)
// {
// 	// Convert screen position to tile coordinates
// 	map_pos->x = viewport_offset.x + ((screen.x - MINIMAP_X) / MINIMAP_TILE_SIZE);
// 	map_pos->y = viewport_offset.y + ((screen.y - MINIMAP_Y) / MINIMAP_TILE_SIZE);
// }

// /* Draw a single tile on the viewport minimap */
// static void draw_viewport_tile(t_cub *cub, int screen_x, int screen_y, t_coord viewport_offset)
// {
// 	t_vec	map_pos;
// 	t_coord	map;

// 	map_pos = (t_vec){0, 0};
// 	screen_to_viewport_coords((t_coord){screen_x, screen_y}, viewport_offset, &map_pos);
// 	map.x = (int)floor(map_pos.x);
// 	map.y = (int)floor(map_pos.y);
// 	// Check if coordinates are within map bounds
// 	if (map.x < 0 || map.x >= (int)cub->map.max_col ||
// 		map.y < 0 || map.y >= (int)cub->map.rows)
// 		return;
// 	if (map.x >= (int)ft_strlen(cub->map.grid[map.y]))
// 		return;

// 	img_pxl_put(&cub->game_img, screen_x, screen_y,
// 		char_to_tile_rgb(cub->map.grid[map.y][map.x]));
// }

void get_viewport_offset(t_cub *cub, t_coord *offset)
{
	int center_x = (int)cub->player.pos.x;
	int center_y = (int)cub->player.pos.y;

	offset->x = center_x - (MINIMAP_VISIBLE_COLS / 2);
	offset->y = center_y - (MINIMAP_VISIBLE_ROWS / 2);

	if (offset->x < 0)
		offset->x = 0;
	if (offset->y < 0)
		offset->y = 0;
	if ((int)cub->map.max_col > MINIMAP_VISIBLE_COLS)
	{
		if (offset->x + MINIMAP_VISIBLE_COLS > (int)cub->map.max_col)
			offset->x = cub->map.max_col - MINIMAP_VISIBLE_COLS;
	}
	else
		offset->x = 0;
	if ((int)cub->map.rows > MINIMAP_VISIBLE_ROWS)
	{
		if (offset->y + MINIMAP_VISIBLE_ROWS > (int)cub->map.rows)
			offset->y = cub->map.rows - MINIMAP_VISIBLE_ROWS;
	}
	else
		offset->y = 0;
}

static void	draw_minimap_pixel(t_cub *cub, int x, int y, t_vec center)
{
	t_vec	map_pos;
	t_coord	map;

	screen_to_map_coords(x, y, center, &map_pos);
	map.x = (int)floor(map_pos.x);
	map.y = (int)floor(map_pos.y);

	// Check if coordinates are within map bounds
	if (map.x >= 0 && map.y >= 0 && map.y < (int)cub->map.rows
		&& map.x < (int)ft_strlen(cub->map.grid[map.y]))
		img_pxl_put(&cub->game_img, x, y, char_to_tile_rgb(cub->map.grid[map.y][map.x]));
}




void render_map(t_cub *cub)
{
	t_vec	center;
	int		x;
	int		y;

	get_minimap_center(cub, &center);

	y = MINIMAP_Y;
	while (y <= MINIMAP_Y + MINIMAP_HEIGHT)
	{
		x = MINIMAP_X;
		while (x <= MINIMAP_X + MINIMAP_WIDTH)
		{
			draw_minimap_pixel(cub, x, y, center);
			x++;
		}
		y++;
	}
}

# endif