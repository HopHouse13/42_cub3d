/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:01:41 by pab               #+#    #+#             */
/*   Updated: 2025/09/25 19:00:03 by pab              ###   ########.fr       */
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

static void	return_start(t_data *data, char * mapfile)
{
	char	*line;
	
	data->fd_file = open(mapfile, O_RDONLY); // reouvre le file au debut
	if (data->fd_file < 0) // pas utile vu qu'on sait qu'il est ouvrable mais utile si table des FD saturee
		exit_door(data, "message probleme d'ouverture du .cub", );	
	while((line = get_next_line(data->fd_file)) // avance jusqu'a la ligne du start de la map en comparant [start] a [line]
			&& (ft_strlen(line) != ft_strlen(data->map.tab_map[0])
			|| ft_strncmp(data->map.tab_map[0], line, ft_strlen(data->map.tab_map[0]))))
		free(line);
	free(line);
}

bool	is_empty(char *line) // non static car utilisation dans check_map
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

static char	*init_map(t_data *data)
{
	char	*line;
	char	*start;
	
	while((line = get_next_line(data->fd_file)) && is_empty(line)) // avance jusqu'a la prochiane ligne non vide
		free(line);
	if (!line)
		exit_door(data, "map inexistante", );
	start = ft_strdup(line); // copie la ligne du start de la map
	free(line);
	data->map.nb_line++; // incrementele compteur de ligne pour malloc le double_taa map car nous avons trouver le start de la map
	while((line = get_next_line(data->fd_file)) && ++data->map.nb_line) // avance ligne par ligne jusqu'a la fin du file en incrementant nb_line
		free(line);
	close(data->fd_file);
	data->map.tab_map = malloc(sizeof(char *) * (data->map.nb_line + 1)); // initialise dinamiquement le double_tab map
	if (!data->map.tab_map)
		exit_door(data, "erreur lors de l'init. de la map", );
	return (start); // le retourne start de la map
}

void	make_copy(t_data *data, char *mapfile)
{
	int		i;
	char	*line;
	char	*start;
	
	i = 1;
	start = init_map(data); // retourne un char * qui est la premiere ligne de la map
	data->map.tab_map[0] = start; // j'ai pas besoin de free start??? parce que l'adresse du pointeur est copie dans data->map.tab_map qui est free
	return_start(data, mapfile);
	while((line = get_next_line(data->fd_file)))
	{
		data->map.tab_map[i++] = ft_strdup(line); // duplique chaque ligne dans le double_tab map jusqu'a la fin du file
		free(line);
	}
	data->map.tab_map[i] = NULL; // met a NULL le dernier pointeur de la chaine de pointeur
	print_map(data->map.tab_map);
}
