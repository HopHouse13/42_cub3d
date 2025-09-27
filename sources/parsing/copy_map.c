/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:01:41 by pab               #+#    #+#             */
/*   Updated: 2025/09/27 16:03:58 by pab              ###   ########.fr       */
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
// je malloc le double tab_map
// je reparcours le fichier en dup chaque ligne dans mon doubel tab_map (il est 5h35 du mat je go dodo)

static void	refind_start_map(t_data *data, char *mapfile, t_error *err_id)
{
	char	*line;

	data->fd_file = open(mapfile, O_RDONLY); // reouvre le file au debut
	if (data->fd_file < 0) // pas utile vu qu'on sait qu'il est ouvrable mais utile si table des FD saturee
		exit_door(data, E_OPEN_FILE);
	while (1)
	{
		line = get_next_line(data->fd_file, err_id, false);
		if (*err_id == E_ALLOC)
			exit_door(data, *err_id);
		if (!line)
			exit_door(data, E_UNKNOWN);
		if (ft_strlen(line) != ft_strlen(data->map.tab_map[0])
			|| ft_strncmp(data->map.tab_map[0], line, ft_strlen(data->map.tab_map[0])))
			break ;
		free(line);
	}
}
// non static car utilisation dans check_map
bool	is_empty(char *line)
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

static char	*init_map(t_data *data, t_error *err_id)
{
	char	*line;
	char	*start;

	while(true) // j'aime pas dutout faire ca
	{
		line = get_next_line(data->fd_file, err_id, false);
		if (*err_id == E_ALLOC)
			exit_door(data, *err_id);
		if(!line)
			exit_door(data, E_EMPTY_MAP);
		else if (!is_empty(line)) // avance jusqu'a la prochiane ligne non vide
			break ;
		free(line);
	}
	start = ft_strdup(line); // copie la ligne du start de la map
	if (!start)
		exit_door(data, E_ALLOC);
	while(!line) // avance ligne par ligne jusqu'a la fin du file en incrementant nb_line
	{
		++data->map.nb_line;
		free(line);
		line = get_next_line(data->fd_file, err_id, false);
		if (*err_id == E_ALLOC)
			exit_door(data, *err_id);
	}
	close(data->fd_file);
	data->map.tab_map = malloc(sizeof(char *) * (data->map.nb_line + 1)); // initialise dinamiquement le double_tab map
	if (!data->map.tab_map)
		exit_door(data, E_ALLOC);
	return (start); // le retourne start de la map
}

void	make_copy(t_data *data, char *mapfile)
{
	int		i;
	char	*line;
	t_error	err_id;
	
	data->map.tab_map[0] = init_map(data, &err_id); // retourne un char * qui est la premiere ligne de la map
	refind_start_map(data, mapfile, &err_id);
	i = 1;
	while(i < data->map.nb_line)
	{
		line = get_next_line(data->fd_file, &err_id, false);
		if (err_id == E_ALLOC)
			exit_door(data, err_id);
		if (!line) // normalement
			break;
		data->map.tab_map[i] = ft_strdup(line); // duplique chaque ligne dans le double_tab map jusqu'a la fin du file
		free(line);
		if (!data->map.tab_map[i])
			exit_door(data, E_ALLOC);
		i++;
	}
	data->map.tab_map[i] = NULL; // met a NULL le dernier pointeur de la chaine de pointeur
	print_map(data->map.tab_map);
}
