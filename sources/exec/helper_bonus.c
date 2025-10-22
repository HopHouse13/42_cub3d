/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:29:20 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/22 20:32:19 by tjacquel         ###   ########.fr       */
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