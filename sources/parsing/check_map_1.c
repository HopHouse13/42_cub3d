/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:07:47 by pbret             #+#    #+#             */
/*   Updated: 2025/10/23 01:19:50 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
