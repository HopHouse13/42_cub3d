/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:47:58 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/23 00:46:29 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	img_pxl_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < WNDW_W && y >= 0 && y < WNDW_H)
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}

int	render_empty_sqr(t_img *img, t_sqr sqr)
{
	int	i;
	int	j;

	i = sqr.y;
	while (i < sqr.y + sqr.side)
	{
		j = sqr.x;
		while (j < sqr.x + sqr.side)
		{
			if (i == sqr.y || i == sqr.y + sqr.side - 1 || j == sqr.x
				|| j == sqr.x + sqr.side - 1)
				img_pxl_put(img, j, i, sqr.color);
			j++;
		}
		i++;
	}
	return (0);
}

int	render_outlined_sqr(t_img *img, t_sqr sqr)
{
	int	i;
	int	j;

	i = sqr.y;
	while (i < sqr.y + sqr.side)
	{
		j = sqr.x;
		while (j < sqr.x + sqr.side)
		{
			if (sqr.side >= 8 && (i == sqr.y || i == sqr.y + sqr.side - 1
					|| j == sqr.x || j == sqr.x + sqr.side - 1))
				img_pxl_put(img, j++, i, 0x000000);
			else
				img_pxl_put(img, j++, i, sqr.color);
		}
		++i;
	}
	return (0);
}

int	render_rect(t_img *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pxl_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}
