/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 04:24:10 by pab               #+#    #+#             */
/*   Updated: 2025/09/26 16:58:24 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	opening_char(char c)
{
	if (c == ' ' || c == '\n')
		return (true);
	return (false);
}

static bool	valid_outline(char **map, char c, int i, int j)
{
	bool	flag;

	flag = true;
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (!map[i - 1][j] || (map[i - 1][j] && opening_char(map[i - 1][j])))
			flag = false;
		if (!map[i + 1][j] || (map[i + 1][j] && opening_char(map[i + 1][j])))
			flag = false;
		if (!map[i][j - 1] || (map[i][j - 1] && opening_char(map[i][j - 1])))
			flag = false;
		if (!map[i][j + 1] || (map[i][j + 1] && opening_char(map[i][j + 1])))
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

static bool	get_player(t_data *data, char c, int i, int j)
{
	static bool	found_one = false;

	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (found_one)
			return (false);
		else
		{
			found_one = true;
			data->player.ori = c;
			data->player.position.x = i;
			data->player.position.y = j;
		}
	}
	return (true);
}

void	check_map(t_data *data, char *mapfile)
{printf("||||| CHECK_MAP |||||\n");
	int		i;
	int		j;
	char	**map;

	make_copy(data, mapfile);
	map = data->map.tab_map;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!valid_char(map[i][j]))
				exit_door(data, E_INV_CHAR_MAP);
			if (!get_player(data, map[i][j], i, j))
				exit_door(data, E_DUP_PLAYER);
			if (map[i][j] == '\n' && (j == 0 || i == data->map.nb_line -1)) // pour gerer la derniere ligne vide de la map (si il y a) et une ligne vide en cours de map
				exit_door(data, E_EMPTY_LINE);
			if (!valid_outline(map, map[i][j], i, j))
				exit_door(data, E_OPEN_MAP);
		}
	}
	printf("Vecteurs du player x[%f] y[%f]\nOrientation du player [%c]\n", data->player.position.x, data->player.position.y, data->player.ori);
	printf("||||| FIN DU PARCING DE LA MAP |||||\n");
}

// only [0] [1] ([N] [S] [E] [W]) [\n]
// si [0] [N] [S] [E] [W] sont bien entoure soit de [0] ou [1]
// si la map a la totalitee de ses lignes non vide. (un espace est non vide. A confirmer avec toto)