/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:12:04 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/18 19:20:31 by tjacquel         ###   ########.fr       */
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
	if (c == 'C')
		return (RGB_GRN);
	return (TILE_FLOOR);
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

void	print_txtr_struct(t_txtr *txtr)
{
	int	i;

	if (!PRINT_DEBUG)
		return ;
	printf("/* ----------------------------    print_txtr_struct\
    -------------------------*/\n");
	i = 0;
	while (i < 4)
	{
		printf("	txtr[%d].mlx_img = %p, .addr = %p, .bpp = %d, .line_end = \
%d, .endian = %d, .width = %d, .height = %d\n",
			i, txtr[i].mlx_img, (void *)txtr[i].addr, txtr[i].bpp, txtr[i].\
line_len, txtr[i].endian, txtr[i].width, txtr[i].height);
		i++;
	}
	printf("/* -----------------------------------------------------\
-------------------------*/\n\n");
}
