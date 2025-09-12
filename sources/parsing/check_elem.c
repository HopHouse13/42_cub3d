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

static void	check_rest_of_line(char **line)
{
	while(**line && **line != '\n')
	{
		if (**line != ' ')
		{
			printf("je suis sorti a `%c` du reste de la ligne `%s`\n", **line, *line);
			exit (1);
		}
		(*line)++;
	}
}

//static void color_getter(t_data *data, char **line, int key_id)
//{
//	//unsigned int		n;

//	//printf("color_getter line = `%s`", *line);

//	//n = 0;
//	//while (*line[n] && *line[n] != ' ' && *line[n] != '\n')
//	//	n++;
//	//printf("n = %d\n", n);
//	//data->elem.path[key_id] = ft_strndup(*line, n);

//	//*line += n;

//	//printf("data->elem.path[%d] = %s", key_id, data->elem.path[key_id]);

//}


static void path_getter(t_data *data, char **line, int key_id)
{
	unsigned int	n;
	char*			temp_line;

	printf("path_getter line = `%s`", *line);
	temp_line = *line;

	n = 0;
	while (**line && **line != ' ' && **line != '\n')
	{
		(*line)++;
		n++;
	}
	printf("n = %d\n", n);

	data->elem.path[key_id] = ft_strndup(temp_line, n);


	printf("data->elem.path[%d] = %s\n", key_id, data->elem.path[key_id]);

}

static bool	key_finder(char **line, t_key id_key)
{
	static const char	*tab_keys[6] = {"NO ", "EA ", "SO ", "WE ", "F ", "C "};

	if ((id_key < F && !ft_strncmp(*line, tab_keys[id_key], 3))
		|| (id_key > WE && !ft_strncmp(*line, tab_keys[id_key], 2)))
	{
		if (id_key < F)
			*line += 3;
		else
			*line += 2;
		return (true);
	}
	return (false);
}

static void	check_line(t_data *data, char *line)
{
	t_key	id_key;

	while (*line && *line == ' ') // les premiers espaces
		line++;
	printf("\n\n\n>>>>>> VALUE_%c\n", *line);
	fflush(stdout);
	id_key = 0;
	while (id_key <= 5)
	{
		if (key_finder(&line, id_key))
		{
			printf("found key number %d\n-------------------------\n", id_key);
			fflush(stdout);
			data->elem.e_counter++;
			while (*line && *line == ' ')
				line++;
			if (id_key < F)
				path_getter(data, &line, id_key);
			//else
			//	color_getter(data, &line, id_key);
			printf("rest of the line after getter function : `%s`", line);
			check_rest_of_line(&line);
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
		{
			while ((line = get_next_line(fd)))
				free(line);
			break ;
		}
	}
	if (data->elem.e_counter < 6)
		exit (1);
	// check_path(data);
	// check_color(data);
}

// TO DO - 
// COLOR_GETTER
// LIGNES VIDES (*avec ou sans espaces)
// check le path (check_path) - sil est valide, sil existe, si les droits sont bons etc.
// check la couleur (check_color) - si c'est bien [0-255]
// check_map
// gestion des free de tout  (des strndup et du gnl)
// message d'erreur et free checker ce quil y a free etc.
