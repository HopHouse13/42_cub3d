/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:34:06 by pbret             #+#    #+#             */
/*   Updated: 2025/10/13 19:38:03 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	init_parsing_data(t_cub *cub)
{
	int	i;
	
	cub->fd_file = -1;
	// struct_map
	cub->map.grid = NULL;
	cub->map.rows = 0;
	cub->map.max_col = 0;
	// struct_play
	cub->player.pos.x = 0.0;
	cub->player.pos.y = 0.0;
	// struct elem
	i = 0;
	while (i < 4)
		cub->elem.path[i++] = NULL;
	i = 0;
	while (i < 3)
	{
		cub->elem.f_values[i] = -1;
		cub->elem.c_values[i++] = -1;
	}
	cub->elem.f_color = -1;
	cub->elem.c_color = -1;
	cub->elem.facing = 0;
	cub->elem.start_line = false;
	cub->elem.e_counter = 0;
}

// fonction qui remplace les '\n' par '\0' de chaque ligne de la map.
// Cela simplifie l'affichage de la minimap.
void	supp_newline(char **map)
{
	int i;
	int	j;
	
	i = -1;
	while (map[++i])
	{
		j= -1;
		while (map[i][++j])
		{
			if (map[i][j] == '\n')
			map[i][j] = '\0';
		}
	}
}