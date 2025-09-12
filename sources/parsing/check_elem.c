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

static void	floor_color(t_data *data, char **line)
{
	unsigned int	n;
	char			*temp_line;
	// char			*temp_color;
	int				i;

	i = 0;
	while (i < 3)
	{
		temp_line = *line;
		n = 0;
		while (**line && **line != ',' && **line != '\n') // attention le comportement me parait bizarre quand plsrs ',' par exemple F 250,,225,40
		{
			if (!ft_isdigit(**line) && **line != ' ') // si le char n'est pas un espace ou pas un chiffre
			{
				printf ("je sors parce que jai trouve le char `%c`\n", **line);
				exit (1);
			}
			(*line)++;
			n++;
		}
		// temp_color = ft_strndup(temp_line, n);
		// printf ("temp_color = %s\n", temp_color);
		// int color = ft_atoi(temp_color);
		// printf ("color = %d\n", color);

		// if (color < 0)
		// 	exit (1);
		if (data->elem.f_value[i] == -1)
			data->elem.f_value[i] = ft_atoi(ft_strndup(temp_line, n)); // ne permet pas de verifier si le malloc de ft_strndup fail ou si ft_atoi renvoie une valeur de retour erreur
		else
		{
			printf ("doublon floor couleur\n");
			exit(1);
		}
		if (**line == ',' && i !=2) // je veux etre certain de pas skip un ',' en fin de RGB par exemple F 250,225,175,
			(*line)++;
		i++;
	}
}

static void	ceiling_color(t_data *data, char **line)
{
	unsigned int	n;
	char			*temp_line;
	char			*temp_color;
	int				i;

	i = 0;

	while (i < 3)
	{
		temp_line = *line;
		n = 0;
		while (**line && **line != ',' && **line != '\n')
		{
			if (!ft_isdigit(**line) && **line != ' ')
			{
				printf ("je sors parce que jai trouve le char `%c`\n", **line);
				exit (1);
			}
			(*line)++;
			n++;
		}
		temp_color = ft_strndup(temp_line, n);
		printf ("temp_color = %s\n", temp_color);
		int color = ft_atoi(temp_color);
		printf ("color = %d\n", color);

		if (color < 0)
			exit (1);
		if (data->elem.c_value[i] == -1)
			data->elem.c_value[i] = color;
		else
		{
			printf ("doublon ceiling couleur\n");
			exit(1);
		}
		if (**line == ',' && i !=2)
			(*line)++;
		// else
		// 	exit (1);

		i++;
	}
}

static void	color_getter(t_data *data, char **line, t_key id_key)
{
	// faudrait essayer de faire differemment je pense parce que virtuellement les fonctions
	// floor_color() et ceiling_color() sont les memes fonctions
	if (id_key == F)
		floor_color(data, line);
	else if (id_key == C)
		ceiling_color(data, line);
	else
	{
		printf("exit color_getter()\n");

		exit (1);
	}
}


static void path_getter(t_data *data, char **line, t_key id_key)
{
	printf("path_getter line = `%s`", *line);

	unsigned int	n;
	char*			temp_line;

	temp_line = *line;
	n = 0;
	while (**line && **line != ' ' && **line != '\n')
	{
		(*line)++;
		n++;
	}
	printf("n = %d\n", n);

	if (!data->elem.path[id_key]) // protection pour eviter les doublons
		data->elem.path[id_key] = ft_strndup(temp_line, n);
	else
	{
		printf("doublon path\n");
		exit(1);
	}


	printf("data->elem.path[%d] = %s\n", id_key, data->elem.path[id_key]);

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
			else
				color_getter(data, &line, id_key);
			printf("rest of the line after getter function : `%s`", line);
			check_rest_of_line(&line);
			return ;
		}
		id_key++;
	}
	if (data->elem.e_counter < 6)
	{
		printf ("pas assez d'elements pour initialiser la map check_line()\n");
		exit (1);
	}
	// exit (1); // sans le if statement au dessus, on exit forcement si ya pas assez d'element pour initialiser la carte
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
	printf ("\n\n----------------------- Elem values after data->elem.e_counter == 6 ---------------------\n");
	print_elem(&data->elem);
	if (data->elem.e_counter < 6)
	{
		printf ("pas assez d'elements pour initialiser la map check_elem()\n");
		exit (1);
	}
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
