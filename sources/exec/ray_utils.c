/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:12:04 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/21 00:22:33 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	date_in_s(t_cub *cub)
{
	double			time;
	struct timeval	current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		cleanup_mlx(cub, MLX_OTHER_ERR);
	time = current_time.tv_sec + current_time.tv_usec / 1000000.0;
	return (time);
}

double	date_in_ms(t_cub *cub)
{
	double			time;
	struct timeval	current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		cleanup_mlx(cub, MLX_OTHER_ERR);
	time = (current_time.tv_sec * 1000.0) + (current_time.tv_usec / 1000.0);
	return (time);
}

t_tile	char_to_tile(char c)
{
	if (c == '0')
		return (TILE_FLOOR);
	if (c == '1')
		return (TILE_WALL);
	if (c == 'E')
		return (TILE_EP);
	if (c == 'S')
		return (TILE_SP);
	if (c == 'W')
		return (TILE_WP);
	if (c == 'N')
		return (TILE_NP);
	if (c == 'C')
		return (TILE_EXTRA);
	return (TILE_FLOOR);
}

uint32_t	char_to_tile_rgb(char c)
{
	if (c == '0')
		return (RGB_FLOOR);
	if (c == '1')
		return (RGB_RED);
	if (c == 'E')
		return (RGB_FLOOR);
	if (c == 'S')
		return (RGB_FLOOR);
	if (c == 'W')
		return (RGB_FLOOR);
	if (c == 'N')
		return (RGB_FLOOR);
	if (c == 'D')
		return (RGB_GRN);
	return (RGG_BLCK);
}

void	print_map_ray(t_map *map)
{
	if (!PRINT_DEBUG)
		return ;
	print_map(map->grid);
	printf("map->rows = %zd\n", map->rows);
	printf("map->max_col = %zd\n", map->max_col);
	printf("map->display_map = %d\n", map->display_map);
}
