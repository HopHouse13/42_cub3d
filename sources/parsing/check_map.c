/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 04:24:10 by pab               #+#    #+#             */
/*   Updated: 2025/10/13 19:57:10 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	open_cell(t_cub *cub,char ** map, int i, int j)
{
	if (i < 0 || i >= (int)cub->map.rows || !map[i]
		|| j < 0 || j >= (int)ft_strlen(map[i]))
		return (true);
	if (!map[i][j] 
		|| (map[i][j] != '1' &&  map[i][j] != '0'
		&&  map[i][j] != 'N' && map[i][j] != 'E'
		&&  map[i][j] != 'S' && map[i][j] != 'W'))
		return (true);
	return (false);
}

void	valid_outline(t_cub *cub)
{
	int	i;
	int	j;
	char **map;
	
	map = cub->map.grid;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (open_cell(cub, map, i -1, j) 
					|| open_cell(cub, map, i +1, j)
					|| open_cell(cub, map, i, j -1)
					|| open_cell(cub, map, i, j +1))
					exit_door(cub, PSG_OPEN_MAP_ERR);
			}
		}
	}
}

void	valid_char(t_cub *cub)
{
	int		i;
	int		j;
	char 	c;

	i = -1;
	while (cub->map.grid[++i])
	{
		j = -1;
		while (cub->map.grid[i][++j])
		{
			c = cub->map.grid[i][j];
			if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E'
				 && c != 'W' && c != ' ' && c != '\n')
				exit_door(cub, PSG_INV_CHAR_MAP_ERR);
		}
	}
}

void	get_player(t_cub *cub)
{
	int		i;
	int		j;
	
	i = -1;
	while (cub->map.grid[++i])
	{
		j = -1;
		while (cub->map.grid[i][++j])
		{
			if ( cub->map.grid[i][j] == 'N' ||  cub->map.grid[i][j] == 'S'
				||  cub->map.grid[i][j] == 'E' ||  cub->map.grid[i][j] == 'W')
			{
				if (cub->elem.facing != '\0')
					exit_door(cub, PSG_DUP_PLAYER_ERR);
				else
				{
					cub->elem.facing =  cub->map.grid[i][j];
					cub->player.pos.x = j;
					cub->player.pos.y = i;
				}
			}
		}
	}
	if (cub->elem.facing == '\0')
		exit_door(cub, PSG_NO_PLAYER_ERR);
}

void	empty_line(t_cub *cub)
{
	int	i;
	int	j;
	
	i = -1;
	while (cub->map.grid[++i])
	{
		j = -1;
		while (cub->map.grid[i][++j])
		{
			if (cub->map.grid[i][j] == '\n'
				&& (j == 0 || i == (int)cub->map.rows -1))
				exit_door(cub, PSG_EMPTY_LINE_ERR);
		}
	}
}
