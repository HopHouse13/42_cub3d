/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init_stuff2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:11:46 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/16 23:19:59 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_images(t_cub *cub)
{
	cub->map_img.mlx_img = mlx_new_image(cub->mlx_pointer,
			cub->window_width,
			cub->window_height);
	if (!cub->map_img.mlx_img)
		cleanup_mlx(cub, MLX_IMG_ERR, NULL);
	cub->game_img.mlx_img = mlx_new_image(cub->mlx_pointer,
			WNDW_W,
			WNDW_H);
	if (!cub->game_img.mlx_img)
		cleanup_mlx(cub, MLX_IMG_ERR, NULL);
	cub->map_img.addr = mlx_get_data_addr(cub->map_img.mlx_img,
			&cub->map_img.bpp,
			&cub->map_img.line_len,
			&cub->map_img.endian);
	cub->game_img.addr = mlx_get_data_addr(cub->game_img.mlx_img,
			&cub->game_img.bpp,
			&cub->game_img.line_len,
			&cub->game_img.endian);
}

void	init_textures(t_cub *cub)
{
	size_t	i;
	int		width;
	int		height;

	i = 0;
	while (i < 4)
	{
		cub->txtr[i].mlx_img = mlx_xpm_file_to_image(cub->mlx_pointer,
				cub->elem.path[i],
				&width,
				&height);
		if (!cub->txtr[i].mlx_img)
			cleanup_mlx(cub, MLX_TXTR_ERR, cub->elem.path[i]);
		cub->txtr[i].width = width;
		cub->txtr[i].height = height;
		cub->txtr[i].pxl = (t_coord){0, 0};
		cub->txtr[i].addr = mlx_get_data_addr(cub->txtr[i].mlx_img,
				&cub->txtr[i].bpp,
				&cub->txtr[i].line_len,
				&cub->txtr[i].endian);
		i++;
	}
	if (cub->game_init)
		print_txtr_struct(cub->txtr);
}

void	init_ray_data(t_ray *ray)
{
	ray->map = (t_coord){0, 0};
	ray->ray_dir = (t_vec){0, 0};
	ray->delta_dist = (t_vec){0, 0};
	ray->side_dist = (t_vec){0, 0};
	ray->step = (t_coord){0, 0};
	ray->perp_wall_dist = 0;
	ray->wall_x = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}
