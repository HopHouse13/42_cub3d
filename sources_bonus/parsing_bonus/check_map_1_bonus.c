/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_1_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:07:47 by pbret             #+#    #+#             */
/*   Updated: 2025/10/23 00:46:29 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

// Traverse the 2D array looking for an empty line.
// After scanning a line, it is considered empty if the index equals zero.
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

// Traverse the 2D map array.
// When a 'D' (door) is found:
// -> Check if characters in all 4 directions exist; if not, error.
// -> Check if the door is not between two vertical walls (top/bottom)
//    or not between two horizontal walls (left/right); otherwise, error.
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
