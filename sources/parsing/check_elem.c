/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:43:41 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/10 15:47:34 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void color_getter(t_data *data, int *i, char key_id)
{
	if(key)
}

void path_getter(t_data *data, int *i, int key_id)
{
	if (key_id == -1)
		return ;
	
	data->elem.path[key_id] = ;
		
}

static void key_finder(t_data *data, char *str, int *i)
{
	
	if (str[*i] == 'N' || str[*i] == 'E')

	/*if (str == "NO") 				//PSEUDOcode et pas PROTO
		path_getter(data, i, 0);
	if (str == "EA")
		path_getter(data, i, 1);
	if (str == "SO")
		path_getter(data, i, 2);
	if (str == "WE")
		path_getter(data, i, 3);

	if (str == 'C')
		color_getter(data, i, 'C');
	if (str == 'F')
		color_getter(data, i, 'F');
	else
		exit (1); // aModif*/
}

static void	check_line(t_data *data, char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == ' ')
			continue ;
	}
	key_finder(data, line, &i);
}

void	check_elem(t_data *data, char *file_map)
{
	int	fd;
	char* line;
	(void) data;

	line = NULL;
	fd = open(file_map, O_RDONLY);
	if (fd < 0)
		{printf("message pprobleme d'ouverture du .cub\n"), exit(1);}
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		check_line(data, line);
		free(line);
		if (data->elem.e_counter == 6)
			break ;
	}
	if (data->elem.e_counter < 6)
		exit (1);
	// check_path(data);
	// check_color(data);
}
