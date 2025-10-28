/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:34:06 by pbret             #+#    #+#             */
/*   Updated: 2025/10/28 18:07:15 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Initialize all parsing variables to ZERO.
void	init_parsing_data(t_cub *cub)
{
	int	i;

	cub->psg.tmp_fd = -1;
	cub->psg.tmp_read = -1;
	cub->psg.fd_file = -1;
	cub->psg.line = NULL;
	cub->map.grid = NULL;
	cub->map.rows = 0;
	cub->map.max_col = 0;
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
}
