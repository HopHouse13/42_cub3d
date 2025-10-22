/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_mlx_stuff_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:10:50 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/23 00:46:29 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

static void	destroy_images(t_cub *cub)
{
	int	i;

	if (cub->game_img.mlx_img)
		mlx_destroy_image(cub->mlx_pointer, cub->game_img.mlx_img);
	i = -1;
	while (++i < 5)
	{
		if (cub->txtr[i].mlx_img)
			mlx_destroy_image(cub->mlx_pointer, cub->txtr[i].mlx_img);
	}
	i = -1;
	while (++i < 10)
	{
		if (cub->sp_txtr[i].mlx_img)
			mlx_destroy_image(cub->mlx_pointer, cub->sp_txtr[i].mlx_img);
	}
}

void	cleanup_mlx(t_cub *cub, char *mlx_err, char *item)
{
	if (cub->doors)
		free(cub->doors);
	if (cub->sprites)
		free(cub->sprites);
	if (cub->mlx_pointer)
		destroy_images(cub);
	if (cub->mlx_window)
		mlx_destroy_window(cub->mlx_pointer, cub->mlx_window);
	if (cub->mlx_pointer)
	{
		mlx_destroy_display(cub->mlx_pointer);
		free(cub->mlx_pointer);
	}
	if (ft_strcmp(mlx_err, OK))
		exit_door (cub, mlx_err, item);
}
