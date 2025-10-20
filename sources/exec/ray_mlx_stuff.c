/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_mlx_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:10:50 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/20 21:36:31 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	destroy_images(t_cub *cub)
{
	size_t	i;

	if (cub->game_img.mlx_img)
		mlx_destroy_image(cub->mlx_pointer, cub->game_img.mlx_img);
	i = 0;
	while (i < 5)
	{
		if (cub->txtr[i].mlx_img)
			mlx_destroy_image(cub->mlx_pointer, cub->txtr[i].mlx_img);
		i++;
	}
}

void	destroy_doors(t_cub *cub)
{
	// size_t	i;

	// i = 0;
	// while (i < cub->elem.doors_nb)
	// {
	// 	if (cub->doors[i])
	// 		free (cub->doors[i]);
	// 	i++;
	// }
	if (cub->doors)
		free(cub->doors);
}

void	cleanup_mlx(t_cub *cub, t_error mlx_err)
{
	destroy_doors(cub);
	if (cub->mlx_pointer)
		destroy_images(cub);
	if (cub->mlx_window)
		mlx_destroy_window(cub->mlx_pointer, cub->mlx_window);
	if (cub->mlx_pointer)
	{
		mlx_destroy_display(cub->mlx_pointer);
		free(cub->mlx_pointer);
	}
	if (mlx_err != OK)
		exit_door (cub, mlx_err, NULL);
}
