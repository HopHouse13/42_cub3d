/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 04:24:10 by pab               #+#    #+#             */
/*   Updated: 2025/09/15 05:35:49 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// idee:
// je lis la lien suivant apres les  6 param
// je check si elle est confirme a la premiere ligne de la map -> sinon exit
// je la stock
// je compte combien de lignes est compose la map (avec celle aue je viens de lire) JAI LE NOMBRE DE LIGNE DE LA MAP
// Je close le fd
// je reouvre un nouvel fd
// et je parcours le fichier jusqu'a ligne de debut de map (strcmp)
// je malloc le double tab_map
// je reparcours le fichier en dup chaque ligne dans mon doubel tab_map (il est 5h35 du mat je go dodo)


void	make_copy(t_data *data)
{
	int		tmp_fd;
	int		count_line;
	char	*line;
	
	get_start_map(data);
	count_line = 0;
	tmp_fd = data->fd_file;
	while ((line = get_next_line(tmp_fd)) && ++count_line)
		free(line);
	data->map.map = malloc(sizeof(char *) * (count_line + 1));
	count_line = -1;
	while((line = get_next_line(data->fd_file)))
	{
		data->map.map[++count_line] = strdup(line);
		free(line);
	}
	data->map.map[++count_line] = NULL;
}

void	check_map(t_data *data)
{
	int	i;
	int	j;
	
	make_copy(data);
	i = -1;
	while(data->map.map[++i])
	{
		j = -1;
		while(data->map.map[i][++j])
		{
			
		}
	}
}

