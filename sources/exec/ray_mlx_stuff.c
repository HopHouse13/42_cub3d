/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_mlx_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:10:50 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/11 19:18:46 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	destroy_images(t_cub *cub)
{
		mlx_destroy_image(cub->mlx_pointer, cub->map_img.mlx_img);
		// mlx_destroy_image(cub->mlx_pointer, cub->background_img.mlx_img);
		mlx_destroy_image(cub->mlx_pointer, cub->game_img.mlx_img);
		for (int i = 0; i < 4; i++)
		{
			if (cub->txtr[i].mlx_img)
				mlx_destroy_image(cub->mlx_pointer, cub->txtr[i].mlx_img);
		}

}

int	close_window(t_cub *cub)
{
	//for (int i = 0; i < 7; i++)
	//	mlx_destroy_image(cub->mlx_pointer, cub->textures[i]);


	// destroy_images(cub);
	// mlx_destroy_window(cub->mlx_pointer, cub->mlx_window);
	// mlx_destroy_display(cub->mlx_pointer);
	// free(cub->mlx_pointer);
	// exit(1);
	//return(1);

	mlx_loop_end(cub->mlx_pointer);
	return (0);
}

void	cleanup_mlx(t_cub *cub, t_error mlx_err)
{
	// Destroy textures

	//for (int i = 0; i < 7; i++)
	//	mlx_destroy_image(cub->mlx_pointer, cub->textures[i]);
	//mlx_destroy_image(cub->mlx_pointer, cub->bckgr_txtr[0]);
	//mlx_destroy_image(cub->mlx_pointer, cub->bckgr_txtr[1]);

	// Destroy image buffers
	// mlx_destroy_image(cub->mlx_pointer, cub->map_img.mlx_img);
	// mlx_destroy_image(cub->mlx_pointer, cub->game_img.mlx_img);
	destroy_images(cub);


	// Destroy window and display
	mlx_destroy_window(cub->mlx_pointer, cub->mlx_window);
	mlx_destroy_display(cub->mlx_pointer);
	free(cub->mlx_pointer);
	if (mlx_err != OK)
		exit_door (cub, mlx_err);
}

void	clear_img(t_img *img, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			img_pxl_put(img, j, i, 0x000000); // Black
			j++;
		}
		i++;
	}
}

