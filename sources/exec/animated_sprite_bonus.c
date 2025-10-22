/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_sprite_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:24:59 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/22 21:22:48 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	sort_sprites(t_sp_sort *sprites, int sprite_nb)
{
	int			i;
	int			j;
	t_sp_sort	temp;

	i = 0;
	while (i < sprite_nb - 1)
	{
		j = 0;
		while (j < sprite_nb - i - 1)
		{
			if (sprites[j].distance < sprites[j + 1].distance)
			{
				temp = sprites[j];
				sprites[j] = sprites[j + 1];
				sprites[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	fill_sorted_sprite_order(t_cub *cub, t_sp_sort *sp_order)
{
	int			i;
	int			active_sprites;
	t_vec		delta;

	active_sprites = 0;
	i = 0;
	while (i < cub->elem.sprite_nb)
	{
		if (cub->sprites[i].active)
		{
			delta.x = cub->sprites[i].pos.x - cub->player.pos.x;
			delta.y = cub->sprites[i].pos.y - cub->player.pos.y;
			sp_order[active_sprites].sprite_idx = i;
			sp_order[active_sprites].distance = delta.x * delta.x
				+ delta.y * delta.y;
			cub->sprites[i].distance = sp_order[active_sprites].distance;
			active_sprites++;
		}
		i++;
	}
	sort_sprites(sp_order, active_sprites);
	return (active_sprites);
}

void	render_all_sprites(t_cub *cub)
{
	t_sp_sort	sp_order[MAX_SPRITES];
	int			i;
	int			active_sprites;

	active_sprites = fill_sorted_sprite_order(cub, sp_order);
	i = 0;
	while (i < active_sprites)
	{
		if (cub->sprites[sp_order[i].sprite_idx].active)
			render_single_sprite(cub, &cub->sprites[sp_order[i].sprite_idx],
				sp_order[i].sprite_idx);
		i++;
	}
}

void	update_sprite_animation(t_sprite *sprite, double frame_time)
{
	sprite->elapsed_time += frame_time;
	if (sprite->elapsed_time >= sprite->frame_duration)
	{
		sprite->elapsed_time = 0.0;
		sprite->current_frame++;
		if (sprite->current_frame >= SP_FRAMES)
		{
			if (sprite->loop)
				sprite->current_frame = 0;
			else
				sprite->current_frame = SP_FRAMES - 1;
		}
	}
}

void	update_all_sprites(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->elem.sprite_nb)
	{
		if (cub->sprites[i].active)
			update_sprite_animation(&cub->sprites[i], cub->player.frame_time);
		if (fabs(cub->player.pos.x - cub->sprites[i].pos.x) < 0.5
			&& fabs(cub->player.pos.y - cub->sprites[i].pos.y) < 0.5)
		{
			cub->sprites[i].active = false;
			print_sprites(cub);
			cub->sprites[i].print_debug = false;
		}
		i++;
	}
}
