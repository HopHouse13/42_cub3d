/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:34:06 by pbret             #+#    #+#             */
/*   Updated: 2025/10/23 00:46:29 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

// Initialize all parsing variables to ZERO.
void	init_parsing_data(t_cub *cub)
{
	int	i;

	cub->psg.fd_file = -1;
	cub->psg.line = NULL;
	cub->map.grid = NULL;
	cub->map.rows = 0;
	cub->map.max_col = 0;
	cub->map.display_map = true;
	cub->player.pos = (t_vec){0.0, 0.0};
	i = 0;
	while (i < 15)
		cub->elem.path[i++] = NULL;
	i = -1;
	while (++i < 3)
	{
		cub->elem.f_values[i] = -1;
		cub->elem.c_values[i] = -1;
	}
	cub->elem.f_color = -1;
	cub->elem.c_color = -1;
	cub->elem.facing = 0;
	cub->elem.start_line = false;
	cub->elem.e_counter = 0;
	cub->elem.doors_nb = 0;
	cub->elem.sprite_nb = 0;
}
