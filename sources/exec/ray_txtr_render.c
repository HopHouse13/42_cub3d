/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_txtr_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:37:47 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/10 19:48:27 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	texture_function(t_cub *cub, t_player *player, t_ray *ray, t_txtr *txtr, int x, double wallX)
{
	int txtr_x;
	(void) player;


	txtr_x = (int)(wallX * (double)(txtr->width));
	if (txtr_x < 0)
		txtr_x = 0;
	if (txtr_x >= txtr->width)
		txtr_x = txtr->width - 1;

	if (ray->side == 0 && ray->ray_dir.x < 0) // NORTH
	{
		// if (cub->print_debug_cub)
		// 	printf("	Ray[%d] ray->side == 0 && ray->ray_dir.x > 0\n", x);
		txtr_x = txtr->width - txtr_x - 1;
	}
	if (ray->side == 1 && ray->ray_dir.y > 0) // EAST
	{
		// if (cub->print_debug_cub)
		// 	printf("	Ray[%d] (ray->side == 1 && ray->ray_dir.y < 0\n", x);
		txtr_x = txtr->width - txtr_x - 1;
	}
	// if (cub->print_debug_cub)
	// 	printf ("	Ray[%d] txtr_x = %d\n", x, txtr_x);



	// How much to increase the texture coordinate per screen pixel
	double	step = 1.0 * txtr->height / ray->line_height;

	// Starting texture coordinate
	double	textPos = (ray->draw_start - WNDW_H / 2 + ray->line_height / 2) * step;
	for (int y = ray->draw_start; y < ray->draw_end; y++)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int	txtr_y = (int)textPos % txtr->height;
		// int	txtr_y = (int)textPos & (txtr->height - 1); // works well only with POWER-OF-2 TXTR SIZES (64x64, etc.)
		textPos += step;

		// Calculate the pixel position in the texture buffer
		int color = *(int *)(txtr->addr + txtr_y * txtr->line_len + (txtr_x * txtr->bpp / 8));
		img_pxl_put(&cub->game_img, x, y, color);
	}





}
