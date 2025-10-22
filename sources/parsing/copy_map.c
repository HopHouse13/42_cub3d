/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:01:41 by pab               #+#    #+#             */
/*   Updated: 2025/10/22 20:38:52 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Replace the '\n' at the end of the line with '\0'.
// Then duplicate the line into new_line and free the original line.
static char	*supp_newline(t_cub *cub, char *line)
{
	int		i;
	char	*new_line;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\n')
			line[i] = '\0';
	}
	new_line = ft_strdup(line);
	if (!new_line)
		exit_door(cub, ALLOC_ERR, NULL);
	free (line);
	return (new_line);
}

// Reopen the source file using its file descriptor.
// Loop through the file, comparing each line with the first map line already
// identified and stored.
static void	refind_start_map(t_cub *cub, char *mapfile, char **err_id)
{
	char	*line;

	cub->psg.fd_file = open(mapfile, O_RDONLY);
	if (cub->psg.fd_file < 0)
		exit_door(cub, PSG_OPEN_FILE_ERR, NULL);
	while (true)
	{
		line = get_next_line(cub->psg.fd_file, err_id, false);
		if (!ft_strcmp(*err_id, ALLOC_ERR))
			exit_door(cub, *err_id, NULL);
		if (!line)
			exit_door(cub, UNKNOWN_ERR, NULL);
		if (!ft_strncmp(cub->map.grid[0], line, ft_strlen(cub->map.grid[0])))
			break ;
		free(line);
	}
	free(line);
}

// Loop that searches for the first line containing something other
// than spaces or '\n'.
// Once found, the function returns a pointer to the found line.
static char	*found_start_map(t_cub *cub, char **err_id)
{
	char	*line;
	bool	found_start;
	int		i;

	found_start = false;
	while (true)
	{
		line = get_next_line(cub->psg.fd_file, err_id, false);
		if (!ft_strcmp(*err_id, ALLOC_ERR))
			exit_door(cub, *err_id, NULL);
		if (!line)
			exit_door(cub, PSG_EMPTY_MAP_ERR, NULL);
		i = -1;
		while (line[++i])
		{
			if (line[i] != ' ' && line[i] != '\n')
				found_start = true;
		}
		if (found_start)
			break ;
		free(line);
	}
	return (line);
}

// Found_start_map stock la premiere line de map dans 'start_map'.
// boucle qui compte le nombre de line de la map.
// Allocation du double_tab avec le bon nombre line.
// supp_newline stock la premiere line de la map dans 1er tableau du double tab.
static void	map_allocation(t_cub *cub, char **err_id)
{
	char	*line;
	char	*start_map;

	start_map = found_start_map(cub, err_id);
	line = NULL;
	while (1)
	{
		++cub->map.rows;
		free(line);
		line = get_next_line(cub->psg.fd_file, err_id, false);
		if (!ft_strcmp(*err_id, ALLOC_ERR))
			exit_door(cub, *err_id, NULL);
		if (!line)
			break ;
	}
	close(cub->psg.fd_file);
	cub->map.grid = ft_calloc(sizeof(char *), (cub->map.rows + 1));
	if (!cub->map.grid)
		exit_door(cub, ALLOC_ERR, NULL);
	cub->map.grid[0] = supp_newline(cub, start_map);
}

// Function that copies the map.
// map_allocation allocates memory for the 2D array.
// refind_start_map resets the file descriptor to the beginning of the map.
// Reads the source file and copies the map into the 2D array.
// supp_newline duplicates the line without the '\n' character.
// Stores the maximum number of characters of the longest line
// (for execution purposes).
void	make_copy(t_cub *cub, char *mapfile)
{
	size_t	i;
	char	*line;
	char	*err_id;

	err_id = OK;
	map_allocation(cub, &err_id);
	refind_start_map(cub, mapfile, &err_id);
	i = 1;
	while (i < cub->map.rows)
	{
		line = get_next_line(cub->psg.fd_file, &err_id, false);
		if (!ft_strcmp(err_id, ALLOC_ERR))
			exit_door(cub, err_id, NULL);
		if (!line)
			break ;
		cub->map.grid[i] = supp_newline(cub, line);
		if (cub->map.max_col < ft_strlen(cub->map.grid[i]))
			cub->map.max_col = ft_strlen(cub->map.grid[i]);
		i++;
	}
	cub->map.grid[i] = NULL;
}
