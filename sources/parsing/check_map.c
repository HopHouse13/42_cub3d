/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 04:24:10 by pab               #+#    #+#             */
/*   Updated: 2025/09/16 15:02:01 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// idee:
// j'avance jusqu'a la ligne non vide apres les 6 paramas
// je check si elle est confirme a la premiere ligne de la map -> sinon exit
// je la stock
// je compte combien de lignes est compose la map (avec celle quw je viens de lire) JAI LE NOMBRE DE LIGNE DE LA MAP
// Je close le fd
// je reouvre un nouvel fd
// et je parcours le fichier jusqu'a ligne de debut de map (strcmp)
// je malloc le double tab_map
// je reparcours le fichier en dup chaque ligne dans mon doubel tab_map (il est 5h35 du mat je go dodo)

static bool	is_empty(char * line)
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

static int	count_map(t_data *data, char *mapfile)
{
	int		count_line;
	char	*line;
	char	*start;
	
	count_line = 0;
	while((line = get_next_line(data->fd_file)) && is_empty(line)) // avance jusqu'a la prochiane ligne non vide
		free(line);
	if (!line)
		exit_door(data, "map inexistante");
		
	start = ft_strdup(line); // copie la ligne du start de la map
	free(line);
	count_line++; // incrementele compteur de ligne pour malloc le double_taa map car nous avons trouver le start de la map
	
	while((line = get_next_line(data->fd_file)) && ++count_line) // avance ligne par ligne jusqu'a la fin du file en incrementant count_line
		free(line);
	close(data->fd_file);
	
	data->map.map = malloc(sizeof(char *) * (count_line + 1)); // initialise dinamiquement le double_tab map
	if (!data->map.map)
		exit_door(data, "erreur lors de l'init. de la map");
	
	data->fd_file = open(mapfile, O_RDONLY); // reouvre le file au debut
	if (data->fd_file < 0) // pas utile vu qu'on sait qu'il est ouvrable
		exit_door(data, "message probleme d'ouverture du .cub");
		
	while((line = get_next_line(data->fd_file)) // avance jusqu'a la ligne du start de la map en comparant [start] a [line]
			&& (ft_strlen(line) != ft_strlen(start)
			|| ft_strncmp(start, line, ft_strlen(start))))
		free(line);
	free(line);
	data->map.map[0] = ft_strdup(start); // stock start dans la premiere chaine de char du double_tab map
	free(start);
	return (count_line); // retourne 
}

void	make_copy(t_data *data, char *mapfile)
{
	int		i;
	char	*line;
	
	i = 1; // la premiere chaine de char est deja remplit en amont, lorsque le debut de la map est trouvee
	count_map(data, mapfile);
	while((line = get_next_line(data->fd_file)) /*&& i < count_line*/)
	{
		data->map.map[i++] = strdup(line); // duplique chaque ligne dans le double_tab map jusqu'a la fin du file
		free(line);
	}
	data->map.map[i] = NULL; // met a NULL le dernier pointeur de la chaine de pointeur
	print_map(data->map.map);
}

void	check_map(t_data *data, char *mapfile)
{
	//int	i;
	//int	j;
	
	make_copy(data, mapfile);
	//i = -1;
	//while(data->map.map[++i])
	//{
	//	j = -1;
	//	while(data->map.map[i][++j])
	//	{
			
	//	}
	//}
}

