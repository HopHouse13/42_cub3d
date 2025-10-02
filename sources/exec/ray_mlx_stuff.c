/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_mlx_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:10:50 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/02 21:01:48 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	destroy_images(t_mlx_data *data)
{
		mlx_destroy_image(data->mlx_pointer, data->map_img.mlx_img);
		// mlx_destroy_image(data->mlx_pointer, data->background_img.mlx_img);
		mlx_destroy_image(data->mlx_pointer, data->game_img.mlx_img);

}

int	close_window(t_mlx_data *data)
{
	//for (int i = 0; i < 7; i++)
	//	mlx_destroy_image(data->mlx_pointer, data->textures[i]);
	

	destroy_images(data);
	mlx_destroy_window(data->mlx_pointer, data->mlx_window);
	mlx_destroy_display(data->mlx_pointer);
	free(data->mlx_pointer);
	exit(1);
	//return(1);
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
			img_pix_put(img, j, i, 0x000000); // Black
			j++;
		}
		i++;
	}
}

