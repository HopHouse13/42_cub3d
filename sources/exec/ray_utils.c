/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:12:04 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/23 00:32:08 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	date_in_s(t_cub *cub)
{
	double			time;
	struct timeval	current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		cleanup_mlx(cub, MLX_OTHER_ERR, NULL);
	time = current_time.tv_sec + current_time.tv_usec / 1000000.0;
	return (time);
}

double	date_in_ms(t_cub *cub)
{
	double			time;
	struct timeval	current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		cleanup_mlx(cub, MLX_OTHER_ERR, NULL);
	time = (current_time.tv_sec * 1000.0) + (current_time.tv_usec / 1000.0);
	return (time);
}

uint32_t	char_to_tile_rgb(char c)
{
	if (c == '0' || c == 'S' || c == 'E' || c == 'N' || c == 'W' || c == 'C')
		return (RGB_BEIGE);
	if (c == '1')
		return (RGB_RED);
	if (c == 'D')
		return (RGB_GRN);
	return (RGG_BLCK);
}
