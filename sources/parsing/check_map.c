/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 04:24:10 by pab               #+#    #+#             */
/*   Updated: 2025/10/22 18:15:43 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


// Deux possibilites de char invalide.
// Le 1er if : si le char n'existe pas.
// Le 2eme if : si le char n'est pas le player, un mur ou un sol.
static bool	open_cell(t_cub *cub, char **map, int i, int j)
{
	if (i < 0 || i >= (int)cub->map.rows || !map[i]
		|| j < 0 || j >= (int)ft_strlen(map[i]))
		return (true);
	if (!map[i][j]
		|| (map[i][j] != '1' && map[i][j] != '0'
		&& map[i][j] != 'N' && map[i][j] != 'E'
		&& map[i][j] != 'S' && map[i][j] != 'W'
		&& map[i][j] != 'D' && map[i][j] != 'C'))
		return (true);
	return (false);
}

// Pourcours du double tab char par char.
// Pour les char '0' ou char 'player', la fonction check le char de charque
// direction avec la fonction open_cell.
// Si open_cell renvoie true, la map est ouverte.
static void	valid_outline(t_cub *cub)
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
				|| map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'D'
				|| map[i][j] == 'C')
			{
				if (open_cell(cub, map, i -1, j)
					|| open_cell(cub, map, i +1, j)
					|| open_cell(cub, map, i, j -1)
					|| open_cell(cub, map, i, j +1))
					exit_door(cub, PSG_OPEN_MAP_ERR, map[i]);
			}
		}
	}
}

// Pourcours du double tab char par char.
// Si un char de la map est un autre char que ceux dans la condition,
// la map est invalide.
static void	valid_char(t_cub *cub)
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
				&& c != 'E' && c != 'W' && c != ' ' && c != 'D' && c != 'C')
				exit_door(cub, PSG_INV_CHAR_MAP_ERR, cub->map.grid[i]);
			if (c == 'D')
				cub->elem.doors_nb++;
			if (c == 'C')
				cub->elem.sprite_nb++;
			if (cub->elem.sprite_nb > MAX_SPRITES)
				exit_door(cub, PSG_COIN_MAX_ERR, ft_itoa(MAX_SPRITES));
		}
	}
}

// Pourcours du double tab char par char.
// Si un char est identifie comme un caractere player et que la varible facing
// est vide, la fonction stock ce char dans cette variable.
static void	get_player(t_cub *cub)
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

// Fonction qui manage le parsing de la map.
void	check_map(t_cub *cub, char *mapfile)
{
	make_copy(cub, mapfile);
	valid_char(cub);
	valid_outline(cub);
	get_player(cub);
	empty_line(cub);
	check_door(cub);
}

