/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:35:29 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/23 00:46:29 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

// Extract fog RGB components
// Blend: (1 - fog_factor) * pxl_color + fog_factor * fog
// Recombine into single pxl_color value
int	add_fog(double distance, int pxl_color)
{
	t_rgb	pxl;
	t_rgb	fog;
	double	fog_factor;

	if (!BONUS || !FOG)
		return (pxl_color);
	fog_factor = distance / FOG_DISTANCE;
	if (fog_factor > 1.0)
		fog_factor = 1.0;
	if (fog_factor < 0.0)
		fog_factor = 0.0;
	pxl.r = (pxl_color >> 16) & 0xFF;
	pxl.g = (pxl_color >> 8) & 0xFF;
	pxl.b = pxl_color & 0xFF;
	fog.r = (FOG_COLOR >> 16) & 0xFF;
	fog.g = (FOG_COLOR >> 8) & 0xFF;
	fog.b = FOG_COLOR & 0xFF;
	pxl.r = (int)((1.0 - fog_factor) * pxl.r + fog_factor * fog.r);
	pxl.g = (int)((1.0 - fog_factor) * pxl.g + fog_factor * fog.g);
	pxl.b = (int)((1.0 - fog_factor) * pxl.b + fog_factor * fog.b);
	pxl_color = (pxl.r << 16) | (pxl.g << 8) | pxl.b;
	return (pxl_color);
}
