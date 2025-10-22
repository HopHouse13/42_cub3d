/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:07:47 by pbret             #+#    #+#             */
/*   Updated: 2025/10/22 16:11:45 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Parcours le double tab a la recherche d'une line vide.
// Apres avoir parcouru la line, une line est identifiee comme vide si l'index
// est egale a zero.
void	empty_line(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map.grid[++i])
	{
		j = 0;
		while (cub->map.grid[i][j])
			j++;
		if (j == 0)
			exit_door(cub, PSG_EMPTY_LINE_ERR, NULL);
	}
}

// Parcours du double tab map.
// found 'D':
// -> check si les char aux 4 directions existent si non erreur.
// -> check Si la porte n’est pas entre deux murs verticalement (haut/bas) ou
// qu’elle n’est pas non plus entre deux murs horizontalement (gauche/droite),
// alors c’est une erreur.
void	check_door(t_cub *cub)
{
	int		i;
	int		j;
	char	**map;

	map = cub->map.grid;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'D')
			{
				if (i -1 < 0 || i +1 >= (int)cub->map.rows || !map[i]
					|| j -1 < 0 || j +1 >= (int)ft_strlen(map[i]))
					exit_door(cub, PSG_DOOR_ERR, map[i]);
				if (!((map[i -1][j] == '1' && map[i +1][j] == '1')
					|| (map[i][j -1] == '1' && map[i][j +1] == '1')))
					exit_door(cub, PSG_DOOR_ERR, map[i]);
			}
		}
	}
}