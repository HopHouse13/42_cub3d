/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 04:24:10 by pab               #+#    #+#             */
/*   Updated: 2025/09/22 21:10:38 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
static bool	is_invalid_outline(char **map, char c, int i, int j)
{
	bool	flag;

	flag = false;
	if (c == 0 || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (i - 1 >= 0 && map[i - 1][j] != '0' && map[i - 1][j] != '1')
			flag = true;
		if (map[i + 1][j] && map[i + 1][j] != '0' && map[i + 1][j] != '1')
			flag = true;
		if (j - 1 >= 0 && map[i][j - 1] != '0' && map[i][j - 1] != '1')
			flag = true;
		if (map[i][j + 1] && map[i][j + 1] != '0' && map[i][j + 1] != '1')
			flag = true;
	}
	return (flag);
}
static bool	is_invalid_char(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
		&& c != ' ' && c != '\n')
		return (true);
	return (false);
}

void	check_map(t_data *data, char *mapfile)
{
	int		i;
	int		j;
	char	**tmp_map;
	
	make_copy(data, mapfile);
	tmp_map = data->map.tab_map;
	i = -1;
	while(tmp_map[++i])
	{
		if (is_empty(tmp_map[i])) // pour gerer les ligne vides dans la map
			exit_door(data, "ligne vide dans la map", ERROR);
		j = -1;
		while(tmp_map[i][++j])
		{
			if (tmp_map[i][j] == '\n' && i == data->map.count_line - 1) // pour gerer la derniere ligne vide de la map (si il y a)
				exit_door(data, "ligne vide dans la map", ERROR);
			if (is_invalid_char(tmp_map[i][j]))
				exit_door(data, "caracte invalide", ERROR);
			if (is_invalid_outline(tmp_map, tmp_map[i][j], i, j))
				exit_door(data, "open map", ERROR);
		}
	}
	//printf("indexe j [%d]\n", j);
	printf("||||| FIN DU PARCING DE LA MAP |||||\n");
}

// only [0] [1] ([N] [S] [E] [W]) [\n]
// si [0] [N] [S] [E] [W] sont bien entoure soit de [0] ou [1]
// si la map a la totalitee de ses lignes non vide. (un espace est non vide. A confirmer avec toto)
