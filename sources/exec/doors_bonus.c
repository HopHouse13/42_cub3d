/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:47:43 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/20 21:09:52 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	count_doors(t_cub *cub)
{
	int		i;
	int		j;

	i = -1;
	while (cub->map.grid[++i])
	{
		j = -1;
		while (cub->map.grid[i][++j])
		{
			if (cub->map.grid[i][j] == 'D')
				cub->elem.doors_nb++;
		}
	}
}

// void	init_single_door(t_cub *cub, int door_idx)
// {
// 	cub->doors[door_idx] = malloc(sizeof(t_door));
// 	if (!cub->doors[door_idx])
// 		cleanup_mlx(cub, MLX_OTHER_ERR);
// }

void	init_doors(t_cub *cub)
{
	int		i;
	int		j;
	int		door_idx;

	door_idx = 0;
	count_doors(cub);
	if (cub->elem.doors_nb == 0)
		return ;
	cub->doors = malloc(sizeof(t_door) * cub->elem.doors_nb);
	if (!cub->doors)
		cleanup_mlx(cub, MLX_OTHER_ERR);
	i = -1;
	while (cub->map.grid[++i])
	{
		j = -1;
		while (cub->map.grid[i][++j])
		{
			if (cub->map.grid[i][j] == 'D')
				cub->doors[door_idx++] = (t_door){(t_coord){i, j}, CLOSED, false};
		}
	}
	print_doors(cub);
}
