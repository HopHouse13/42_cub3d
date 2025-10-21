/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 04:24:10 by pab               #+#    #+#             */
/*   Updated: 2025/10/21 19:58:29 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Deux possibilites de char invalide.
// Le 1er if : si le char n'existe pas.
// Le 2eme if : si le char n'est pas le player, un mur ou un sol.
bool	open_cell(t_cub *cub, char **map, int i, int j)
{
	if (i < 0 || i >= (int)cub->map.rows || !map[i]
		|| j < 0 || j >= (int)ft_strlen(map[i]))
		return (true);
	if (!map[i][j]
		|| (map[i][j] != '1' && map[i][j] != '0'
		&& map[i][j] != 'N' && map[i][j] != 'E'
		&& map[i][j] != 'S' && map[i][j] != 'W'
		&& map[i][j] != 's' && map[i][j] != 'D')) //bonus
		return (true);
	return (false);
}

bool	correct_wall(t_cub *cub, char **map, int i, int j)
{
		if (i < 0 || i >= (int)cub->map.rows || !map[i]
		|| j < 0 || j >= (int)ft_strlen(map[i]))
		return (true);
	if (!map[i][j]
		|| (map[i][j] != '1' && map[i][j] != '0'
		&& map[i][j] != 'N' && map[i][j] != 'E'
		&& map[i][j] != 'S' && map[i][j] != 'W'
		&& map[i][j] != 's' && map[i][j] != 'D')) //bonus
		return (true);
	return (false);
}

// Pourcours du double tab char par char.
// Pour les char '0' ou char 'player', la fonction check le char de charque
// direction avec la fonction open_cell.
// Si open_cell renvoie true, la map est ouverte.
void	valid_outline(t_cub *cub)
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
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 's') // bonus
			{
				if (open_cell(cub, map, i -1, j)
					|| open_cell(cub, map, i +1, j)
					|| open_cell(cub, map, i, j -1)
					|| open_cell(cub, map, i, j +1))
					exit_door(cub, PSG_OPEN_MAP_ERR, map[i]);
			}
			if (map[i][j] == 'D' && (correct_wall(cub, map, i, j))) // bonus
				exit_door(cub, )
			
				`
		}
	}
}

// Pourcours du double tab char par char.
// Si un char de la map est un autre char que ceux dans la condition,
// la map est invalide.
void	valid_char(t_cub *cub)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	while (cub->map.grid[++i])
	{
		j = -1;
		while (cub->map.grid[i][++j])
		{
			c = cub->map.grid[i][j];
			if (c != '1' && c != '0' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W' && c != ' ' && c != 'D' && c != 's') // bonus
				exit_door(cub, PSG_INV_CHAR_MAP_ERR, cub->map.grid[i]);
		}
	}
}

// Pourcours du double tab char par char.
// Si un char est identifie comme un caractere player et que la varible facing
// est vide, la fonction stock ce char dans cette variable.
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
			if (cub->map.grid[i][j] == 'N' || cub->map.grid[i][j] == 'S'
				|| cub->map.grid[i][j] == 'E' || cub->map.grid[i][j] == 'W')
			{
				if (cub->elem.facing != '\0')
					exit_door(cub, PSG_DUP_PLAYER_ERR, cub->map.grid[i]);
				else
				{
					cub->elem.facing = cub->map.grid[i][j];
					cub->player.pos.x = j;
					cub->player.pos.y = i;
				}
			}
		}
	}
	if (cub->elem.facing == '\0')
		exit_door(cub, PSG_NO_PLAYER_ERR, NULL);
}

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
