/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 04:24:10 by pab               #+#    #+#             */
/*   Updated: 2025/10/23 00:46:29 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

// Two possibilities for invalid characters.
// First if: the character does not exist.
// Second if: the character is not a player, wall, or floor.
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

// Traverse the 2D array character by character.
// For '0' characters or player characters, the function checks each surrounding
// cell using the 'open_cell' function.
// If 'open_cell' returns true, the map is considered open.
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

// Traverse the 2D array character by character.
// If a map character is not one of the allowed characters, the map is invalid.
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
				exit_door(cub, PSG_SP_MAX_ERR, NULL);
		}
	}
}

// Traverse the 2D array character by character.
// If a character is identified as a player and the 'facing' variable is empty,
// the function stores this character in the variable.
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

// Function that handles the parsing of the map.
void	check_map(t_cub *cub, char *mapfile)
{
	make_copy(cub, mapfile);
	valid_char(cub);
	valid_outline(cub);
	get_player(cub);
	empty_line(cub);
	check_door(cub);
}
