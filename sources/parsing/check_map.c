/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 04:24:10 by pab               #+#    #+#             */
/*   Updated: 2025/10/06 19:21:29 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	open_cell(t_cub *cub, char **map, size_t i, size_t j)
{
	if (i < 0 || i >= cub->map.rows || !map[i]
		|| j < 0 || (size_t)j >= ft_strlen(map[i]))
		return (true);
	if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N'
		&& map[i][j] != 'E' && map[i][j] != 'S' && map[i][j] != 'W')
		return (true);
	return (false);
}

static bool	valid_outline(t_cub *cub, char **map, char c, size_t i, size_t j)
{
	bool	flag;

	flag = true;
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (open_cell(cub, map, i -1, j))
			flag = false;
		if (open_cell(cub, map, i +1, j))
			flag = false;
		if (open_cell(cub, map, i, j -1))
			flag = false;
		if (open_cell(cub, map, i, j +1))
			flag = false;
	}
	return (flag);
}

static bool	valid_char(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
		&& c != ' ' && c != '\n')
		return (false);
	return (true);
}

static bool	get_player(t_cub *cub, char c, size_t i, size_t j)
{
	static bool	found_one = false;

	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (found_one)
			return (false);
		else
		{
			found_one = true;
			cub->player.facing = c;
			cub->elem.facing = c;
			cub->player.pos.x = j;
			cub->player.pos.y = i;
		}
	}
	return (true);
}

void	check_map(t_cub *cub, char *mapfile)
{printf("||||| CHECK_MAP |||||\n");
	size_t		i;
	size_t		j;
	char	**map;

	make_copy(cub, mapfile);
	map = cub->map.grid;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!valid_char(map[i][j]))
				exit_door(cub, E_INV_CHAR_MAP);
			if (!valid_outline(cub, map, map[i][j], i, j))
				exit_door(cub, E_OPEN_MAP);
			if (!get_player(cub, map[i][j], i, j))
				exit_door(cub, E_DUP_PLAYER);
			if (map[i][j] == '\n' && (j == 0 || i == cub->map.rows -1)) // pour gerer la derniere ligne vide de la map (si il y a) et une ligne vide en cours de map
				exit_door(cub, E_EMPTY_LINE);
		}
	}
	if (cub->player.facing == '\0')
		exit_door(cub, E_NO_PLAYER);
	printf("Coordonees du player x[%.4ff] y[%.4ff]\nOrientation du player [%c]\n", cub->player.pos.x, cub->player.pos.y, cub->player.facing);
	printf("||||| FIN DU PARSING DE LA MAP |||||\n");
}

// only [0] [1] ([N] [S] [E] [W]) [\n]
// si [0] [N] [S] [E] [W] sont bien entoure soit de [0] ou [1]
// si la map a la totalitee de ses lignes non vide. (un espace est non vide. A confirmer avec toto)