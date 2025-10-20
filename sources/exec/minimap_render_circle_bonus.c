/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_circle_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:04:50 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/20 17:49:55 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#if MAP_MODE == MAP_CIRCLE
/* Check if pixel is within circular minimap boundary */
bool	is_in_minimap_circle(int x, int y)
{
	int	dx;
	int	dy;
	int	distance_sq;

	dx = x - MINIMAP_CENTER_X;
	dy = y - MINIMAP_CENTER_Y;
	distance_sq = dx * dx + dy * dy;
	return (distance_sq <= MINIMAP_RADIUS * MINIMAP_RADIUS);
}

/* Convert screen pixel to map coordinates relative to player */
	// Convert screen position to relative offset from center
	// Add player position to get map coordinates
static void	screen_to_map_coords(int screen_x, int screen_y, t_player *player,
		t_vec *map_coords)
{
	float	rel_x;
	float	rel_y;

	rel_x = (screen_x - MINIMAP_CENTER_X) / (float)MINIMAP_SCALE;
	rel_y = (screen_y - MINIMAP_CENTER_Y) / (float)MINIMAP_SCALE;
	map_coords->x = player->pos.x + rel_x;
	map_coords->y = player->pos.y + rel_y;
}

/* Draw a single pixel of the minimap */
	// Check if coordinates are within map bounds
	// Draw border
static void	draw_minimap_pixel(t_cub *cub, int x, int y)
{
	t_vec	map_pos;
	int		map_x;
	int		map_y;

	screen_to_map_coords(x, y, &cub->player, &map_pos);
	map_x = (int)floor(map_pos.x);
	map_y = (int)floor(map_pos.y);
	if (map_x >= 0 && map_y >= 0 && map_y < (int)cub->map.rows
		&& map_x < (int)ft_strlen(cub->map.grid[map_y]))
		img_pxl_put(&cub->game_img, x, y,
			char_to_tile_rgb(cub->map.grid[map_y][map_x]));
	else
		img_pxl_put(&cub->game_img, x, y, 0x111111);
	if (sqrt(pow(x - MINIMAP_CENTER_X, 2) + pow(y - MINIMAP_CENTER_Y, 2))
		>= MINIMAP_RADIUS - 2)
		img_pxl_put(&cub->game_img, x, y, 0xFFFFFF);
}

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
}
#endif
