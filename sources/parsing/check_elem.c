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

//static void color_getter(t_data *data, int *i, char key_id)
//{
//	if(key)
//}

//static void path_getter(t_data *data, int *i, int key_id)
//{
//	if (key_id == -1)
//		return ;

//	data->elem.path[key_id] = ;

//}

//static int key_finder(t_data *data, char *str, int *i)
//{


//	/*if (str == "NO") 				//PSEUDOcode et pas PROTO
//		path_getter(data, i, 0);
//	if (str == "EA")
//		path_getter(data, i, 1);
//	if (str == "SO")
//		path_getter(data, i, 2);
//	if (str == "WE")
//		path_getter(data, i, 3);

//	if (str == 'C')
//		color_getter(data, i, 'C');
//	if (str == 'F')
//		color_getter(data, i, 'F');
//	else
//		exit (1); // aModif*/
//}
// static void	init_tab_keys(void)
// {

// }


static bool	key_finder(char *line, t_key id_key)
{
	static const char	*tab_keys[6] = {"NO ", "EA ", "SO ", "WE ", "F ", "C "};

	if ((id_key < F && !ft_strncmp(line, tab_keys[id_key], 3))
		|| (id_key > WE && !ft_strncmp(line, tab_keys[id_key], 2)))
		return (true);
	return (false);
}

static void	check_line(t_data *data, char *line)
{
	t_key	id_key;

	while (*line && *line == ' ')
		line++;
	printf("\n\n\n>>>>>> VALUE_%c\n", *line);
	fflush(stdout);
	id_key = 0;
	while (id_key <= 5)
	{
		if (key_finder(line, id_key))
		{
			printf("found key number %d\n-------------------------\n", id_key);
			fflush(stdout);
			data->elem.e_counter++;
			// path_getter(data, id_key);
			return ;
		}
		id_key++;
	}
	exit (1);
}

void	check_elem(t_data *data, char *file_map)
{
	int	fd;
	char* line;
	(void) data;

	line = NULL;
	fd = open(file_map, O_RDONLY);
	if (fd < 0)
		{printf("message probleme d'ouverture du .cub\n"), exit(1);}
	while ((line = get_next_line(fd)))
	{
		// printf("%s", line);
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
