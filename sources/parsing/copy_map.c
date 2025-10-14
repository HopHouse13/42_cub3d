/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:01:41 by pab               #+#    #+#             */
/*   Updated: 2025/10/13 20:57:43 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// idee:
// j'avance jusqu'a la ligne non vide apres les 6 paramas
// je stock la ligne
// je compte combien de lignes est compose la map (avec celle quw je viens de lire) JAI LE NOMBRE DE LIGNE DE LA MAP
// Je close le fd
// je reouvre un nouvel fd
// et je parcours le fichier jusqu'a ligne de debut de map (strcmp)
// je malloc le double grid
// je reparcours le fichier en dup chaque ligne dans mon doubel grid (il est 5h35 du mat je go dodo)

static void	refind_start_map(t_cub *cub, char *mapfile, t_error *err_id)
{
	char	*line;

	cub->fd_file = open(mapfile, O_RDONLY); // reouvre le file au debut
	if (cub->fd_file < 0) // pas utile vu qu'on sait qu'il est ouvrable mais utile si table des FD saturee
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

static bool	is_empty(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (false);
	}
	return (true);
}

static char	*init_map(t_cub *cub, t_error *err_id)
{
	char	*line;
	char	*start;

	while(true) // j'aime pas dutout faire ca
	{
		line = get_next_line(cub->fd_file, err_id, false);
		if (*err_id == PSG_ALLOC_ERR)
			exit_door(cub, *err_id);
		if(!line)
			exit_door(cub, PSG_EMPTY_MAP_ERR);
		else if (!is_empty(line)) // avance jusqu'a la prochiane ligne non vide
			break ;
		free(line);
	}
	start = ft_strdup(line); // copie la ligne du start de la map
	if (!start)
		exit_door(cub, PSG_ALLOC_ERR);
	while(line) // avance ligne par ligne jusqu'a la fin du file en incrementant rows
	{
		++cub->map.rows;
		free(line);
		line = get_next_line(cub->fd_file, err_id, false);
		if (*err_id == PSG_ALLOC_ERR)
			exit_door(cub, *err_id);
	}
	close(cub->fd_file);
	cub->map.grid = malloc(sizeof(char *) * (cub->map.rows + 1)); // initialise dynamiquement le double_tab map
	if (!cub->map.grid)
		exit_door(cub, PSG_ALLOC_ERR);
	return (start); // le retourne start de la map
}

void	make_copy(t_cub *cub, char *mapfile)
{
	size_t	i;
	char	*line;
	t_error	err_id;

	err_id = OK; // value de non erreur
	cub->map.grid[0] = init_map(cub, &err_id); // retourne un char * qui est la premiere ligne de la map
	refind_start_map(cub, mapfile, &err_id);
	i = 1;
	while(i < cub->map.rows)
	{
		line = get_next_line(cub->fd_file, &err_id, false);
		if (err_id == PSG_ALLOC_ERR)
			exit_door(cub, err_id);
		if (!line) // normalement
			break;
		cub->map.grid[i] = ft_strdup(line); // duplique chaque ligne dans le double_tab map jusqu'a la fin du file
		free(line);
		if (!cub->map.grid[i])
			exit_door(cub, PSG_ALLOC_ERR);
		if (cub->map.max_col < ft_strlen(cub->map.grid[i]))
			cub->map.max_col = ft_strlen(cub->map.grid[i]);
		i++;
	}
	cub->map.grid[i] = NULL; // met a NULL le dernier pointeur de la chaine de pointeur
}

// fonction de management del a verification de la map
void	check_map(t_cub *cub, char *mapfile)
{
	make_copy(cub, mapfile);
	valid_char(cub);
	valid_outline(cub);
	get_player(cub);
	empty_line(cub);
	supp_newline(cub->map.grid);
}
