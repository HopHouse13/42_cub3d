/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init_stuff2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:11:46 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/23 00:46:29 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	init_sp_txtr(t_cub *cub)
{
	size_t	i;
	t_key	sp_idx;
	int		width;
	int		height;

	i = 0;
	sp_idx = s0;
	while (i < 10)
	{
		cub->sp_txtr[i].mlx_img = mlx_xpm_file_to_image(cub->mlx_pointer,
				cub->elem.path[sp_idx], &width, &height);
		if (!cub->sp_txtr[i].mlx_img)
			cleanup_mlx(cub, MLX_TXTR_ERR, cub->elem.path[sp_idx]);
		cub->sp_txtr[i].width = width;
		cub->sp_txtr[i].height = height;
		cub->sp_txtr[i].pxl = (t_coord){0, 0};
		cub->sp_txtr[i].addr = mlx_get_data_addr(cub->sp_txtr[i].mlx_img,
				&cub->sp_txtr[i].bpp,
				&cub->sp_txtr[i].line_len,
				&cub->sp_txtr[i].endian);
		sp_idx++;
		i++;
	}
	if (cub->game_init)
		print_sp_txtr_struct(cub->sp_txtr);
}

void	init_image(t_cub *cub)
{
	cub->game_img.mlx_img = mlx_new_image(cub->mlx_pointer,
			WNDW_W,
			WNDW_H);
	if (!cub->game_img.mlx_img)
		cleanup_mlx(cub, MLX_IMG_ERR, NULL);
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
	while (i < 5)
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
