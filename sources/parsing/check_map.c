/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 04:24:10 by pab               #+#    #+#             */
/*   Updated: 2025/10/11 20:44:02 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	open_cell(t_cub *cub,char ** map, int i, int j)
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

static void	valid_outline(t_cub *cub)
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

static void	valid_char(t_cub *cub)
{
	int	i;
	int	j;
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

static void	get_player(t_cub *cub)
{
	int	i;
	int	j;
	char	c;
	
	i = -1;
	while (cub->map.grid[++i])
	{
		j = -1;
		while (cub->map.grid[i][++j])
		{
			c = cub->map.grid[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (cub->elem.facing != '\0')
					exit_door(cub, PSG_DUP_PLAYER_ERR);
				else
				{
					cub->elem.facing = c;
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

void	check_map(t_cub *cub, char *mapfile)
{
	make_copy(cub, mapfile);
	valid_char(cub);
	valid_outline(cub);
	get_player(cub);
	empty_line(cub);
}

// 'make_copy' copie la map dans un double tab nomme "grid"
// Double boucle pour parcourir chaque char de "grid"
// Pour chaque char:
// * Check de la validation du char
// * check que ce char soit entoure de mur (1)
// * check qu'il y a un player et un seul et stock les informations si player.
// * chexk si la ligne est vide ou pas
// a la fin de la boucle j'enregiste la valeur de char qu'a la plus grande ligne
//  (max_col)
//void	check_map(t_cub *cub, char *mapfile)
//{
//	int		i;
//	int		j;

//	make_copy(cub, mapfile);
//	i = -1;
//	while (cub->map.grid[++i])
//	{
//		j = -1;
//		while (cub->map.grid[i][++j])
//		{
//			if (!valid_char(cub->map.grid[i][j]))
//				exit_door(cub, PSG_INV_CHAR_MAP_ERR);
//			if (!valid_outline(cub, cub->map.grid, cub->map.grid[i][j], i, j))
//				exit_door(cub, PSG_OPEN_MAP_ERR);
//			if (!get_player(cub, cub->map.grid[i][j], i, j))
//				exit_door(cub, PSG_DUP_PLAYER_ERR);
//			if (cub->map.grid[i][j] == '\n' && (j == 0 || i == cub->map.rows -1))
//				exit_door(cub, PSG_EMPTY_LINE_ERR);
//			if (j > cub->map.max_col)
//				cub->map.max_col = j;
//		}
//	}
//	if (cub->elem.facing == '\0')
//		exit_door(cub, PSG_NO_PLAYER_ERR);
//}
