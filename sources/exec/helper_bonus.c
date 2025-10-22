/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:29:20 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/22 20:36:02 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	update_bonus(t_cub *cub)
{
	if (!BONUS)
		return ;
	update_doors(cub);
	update_all_sprites(cub);
}

void	render_bonus(t_cub *cub)
{
	if (!BONUS)
		return ;
	render_all_sprites(cub);
	if (cub->player.kbrd.key_m == true)
	{
		render_map(cub);
		render_2dray(cub, &(cub->player));
	}
}

void	save_ray_buffer(t_cub *cub, t_ray *ray, int x)
{
	cub->buff[x].side = ray->side;
	cub->buff[x].map.x = ray->map.x;
	cub->buff[x].map.y = ray->map.y;
	cub->buff[x].step.x = ray->step.x;
	cub->buff[x].step.y = ray->step.y;
	cub->buff[x].ray_dir.x = ray->ray_dir.x;
	cub->buff[x].ray_dir.y = ray->ray_dir.y;
	cub->buff[x].perp_wall_dist = ray->perp_wall_dist;
}
