/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_sprite_init_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:42:19 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/23 00:46:29 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

static void	init_single_sprite(t_sprite *sprite, int x, int y)
{
	sprite->pos = (t_vec){x + 0.5, y + 0.5};
	sprite->active = true;
	sprite->current_frame = 0;
	sprite->frame_duration = 0.2;
	sprite->elapsed_time = 0.0;
	sprite->distance = 0.0;
	sprite->loop = true;
	sprite->print_debug = true;
}

void	init_sprites(t_cub *cub)
{
	int	i;
	int	j;
	int	sprite_idx;

	sprite_idx = 0;
	if (cub->elem.sprite_nb == 0)
		return ;
	cub->sprites = malloc(sizeof(t_sprite) * cub->elem.sprite_nb);
	if (!cub->sprites)
		cleanup_mlx(cub, ALLOC_ERR, NULL);
	i = -1;
	while (cub->map.grid[++i])
	{
		j = -1;
		while (cub->map.grid[i][++j])
		{
			if (cub->map.grid[i][j] == 'C')
			{
				init_single_sprite(&cub->sprites[sprite_idx], j, i);
				sprite_idx++;
			}
		}
	}
	print_sprites(cub);
}
