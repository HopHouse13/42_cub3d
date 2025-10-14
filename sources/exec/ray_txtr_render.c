/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_txtr_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:37:47 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/14 22:00:32 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render_texture(t_cub *cub, t_ray *ray, t_txtr *txtr, int x, double wallX)
{
	int		y;
	int		color;
	double	step;
	double	text_pos;

	txtr->coord.x = (int)(wallX * (double)(txtr->width));
	if (txtr->coord.x < 0)
		txtr->coord.x = 0;
	if (txtr->coord.x >= txtr->width)
		txtr->coord.x = txtr->width - 1;
	if (ray->side == 0 && ray->ray_dir.x < 0)
		txtr->coord.x = txtr->width - txtr->coord.x - 1;
	if (ray->side == 1 && ray->ray_dir.y > 0)
		txtr->coord.x = txtr->width - txtr->coord.x - 1;
	step = 1.0 * txtr->height / ray->line_height;
	text_pos = (ray->draw_start - WNDW_H / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		txtr->coord.y = (int)text_pos % txtr->height;
		text_pos += step;
		color = *(int *)(txtr->addr + (int)txtr->coord.y * txtr->line_len + ((int)txtr->coord.x * txtr->bpp / 8));
		img_pxl_put(&cub->game_img, x, y, color);
		y++;
	}
}
