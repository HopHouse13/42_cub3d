/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:01:41 by pab               #+#    #+#             */
/*   Updated: 2025/10/15 16:34:30 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Reouvre le fichier source avec son FD.
// Boucle qui parcours le fichier et qui compare line par line avec la premiere
// line de la map deja indentifee et stockee.
static void	refind_start_map(t_cub *cub, char *mapfile, t_error *err_id)
{
	char	*line;

	cub->fd_file = open(mapfile, O_RDONLY);
	if (cub->fd_file < 0)
		exit_door(cub, PSG_OPEN_FILE_ERR);
	while (true)
	{
		line = get_next_line(cub->fd_file, err_id, false);
		if (*err_id == PSG_ALLOC_ERR)
			exit_door(cub, *err_id);
		if (!line)
			exit_door(cub, UNKNOWN_ERR);
		if (!ft_strncmp(cub->map.grid[0], line, ft_strlen(cub->map.grid[0])))
			break ;
		free(line);
	}
	free(line);
}

// Boucle qui cherche la premiere line qui a autre chose que des espace ou '\n'.
// Quand elle est trouvee, la fonction renvoie le pointeur de la line trouvee.
static char	*found_start_map(t_cub *cub, t_error *err_id)
{
	char	*line;
	bool	found_start;
	int		i;

	found_start = false;
	while (true)
	{
		line = get_next_line(cub->fd_file, err_id, false);
		if (*err_id == PSG_ALLOC_ERR)
			exit_door(cub, *err_id);
		if (!line)
			exit_door(cub, PSG_EMPTY_MAP_ERR);
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
static void	map_allocation(t_cub *cub, t_error *err_id)
{
	char	*line;
	char	*start_map;

	start_map = found_start_map(cub, err_id);
	line = NULL;
	while (1)
	{
		++cub->map.rows;
		free(line);
		line = get_next_line(cub->fd_file, err_id, false);
		if (*err_id == PSG_ALLOC_ERR)
			exit_door(cub, *err_id);
		if (!line)
			break ;
	}
	close(cub->fd_file);
	cub->map.grid = ft_calloc(sizeof(char *), (cub->map.rows + 1));
	if (!cub->map.grid)
		exit_door(cub, PSG_ALLOC_ERR);
	cub->map.grid[0] = supp_newline(cub, start_map);
}

// Fonction qui copie la map.
// map_allocation alloue la memoire du double tab.
// refind_start_map re place le FD au debout de la map.
// boule qui lit le fichier source et copie la map dans le double tab.
// supp_newline dup la line sans le '\n'.
// stock le plus grand nombre de char del a plus grande line(pour l'exec).
void	make_copy(t_cub *cub, char *mapfile)
{
	size_t	i;
	char	*line;
	t_error	err_id;

	err_id = OK;
	map_allocation(cub, &err_id);
	refind_start_map(cub, mapfile, &err_id);
	i = 1;
	while (i < cub->map.rows)
	{
		line = get_next_line(cub->fd_file, &err_id, false);
		if (err_id == PSG_ALLOC_ERR)
			exit_door(cub, err_id);
		if (!line)
			break ;
		cub->map.grid[i] = supp_newline(cub, line);
		if (cub->map.max_col < ft_strlen(cub->map.grid[i]))
			cub->map.max_col = ft_strlen(cub->map.grid[i]);
		i++;
	}
	cub->map.grid[i] = NULL;
}

// Fonction qui manage le parsing de la map.
void	check_map(t_cub *cub, char *mapfile)
{
	make_copy(cub, mapfile);
	valid_char(cub);
	valid_outline(cub);
	get_player(cub);
	empty_line(cub);
}
