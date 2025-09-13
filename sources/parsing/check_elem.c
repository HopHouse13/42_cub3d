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

//static void	floor_color(t_data *data, char **line)
//{
//	unsigned int	n;
//	char			*tmp_line;
//	// char			*tmp_color;
//	int				i;

//	i = 0;
//	while (i < 3)
//	{
//		tmp_line = *line;
//		n = 0;
//		while (**line && **line != ',' && **line != '\n') // attention le comportement me parait bizarre quand plsrs ',' par exemple F 250,,225,40
//		{
//			if (!ft_isdigit(**line) && **line != ' ') // si le char n'est pas un espace ou pas un chiffre
//			{
//				printf ("je sors parce que jai trouve le char `%c`\n", **line);
//				exit (1);
//			}
//			(*line)++;
//			n++;
//		}
//		// tmp_color = ft_strndup(tmp_line, n);
//		// printf ("tmp_color = %s\n", tmp_color);
//		// int color = ft_atoi(tmp_color);
//		// printf ("color = %d\n", color);

//		// if (color < 0)
//		// 	exit (1);
//		if (data->elem.f_value[i] == -1)
//			data->elem.f_value[i] = ft_atoi(ft_strndup(tmp_line, n)); // ne permet pas de verifier si le malloc de ft_strndup fail (return NULL) ou si ft_atoi renvoie une valeur de retour erreur (-1 si endehors du scope d'un int)
//		else
//		{
//			printf ("doublon floor couleur\n");
//			exit(1);
//		}
//		if (**line == ',' && i != 2) // je veux etre certain de pas skip un ',' en fin de RGB par exemple F 250,225,175,
//			(*line)++;
//		i++;
//	}
//}

//static void	ceiling_color(t_data *data, char **line)
//{
//	unsigned int	n;
//	char			*tmp_line;
//	char			*tmp_color;
//	int				i;

//	i = 0;

//	while (i < 3)
//	{
//		tmp_line = *line;
//		n = 0;
//		while (**line && **line != ',' && **line != '\n')
//		{
//			if (!ft_isdigit(**line) && **line != ' ') // exit lorsque on rencontre un '-' (moins)
//			{
//				printf ("je sors parce que jai trouve le char `%c`\n", **line);
//				exit (1);
//			}
//			(*line)++;
//			n++;
//		}
//		tmp_color = ft_strndup(tmp_line, n);
//		printf ("tmp_color = %s\n", tmp_color);
//		int color = ft_atoi(tmp_color);
//		printf ("color = %d\n", color);
//		if (color < 0) // pour moi pas utile car les valeurs forcement positive (vu qu'on exit pour '-')
//			exit (1);
//		if (data->elem.c_value[i] == -1)
//			data->elem.c_value[i] = color;
//		else
//		{
//			printf ("doublon ceiling couleur\n");
//			exit(1);
//		}
//		if (**line == ',' && i != 2)
//			(*line)++;
//		// else
//		// 	exit (1);
//		i++;
//	}
//}

// gestion des caracteres entre les digits; passage sur la totalite de la line; seule condition avoir une seule ','entre chaque digits.
static void	handle_between_value(char **line)
{
	bool	comma;
	int		i;

	comma = true;
	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == ',' && comma == true)
			{printf("Manque une valeur entre deux comma\n"), exit(1);}
		else if(ft_isdigit((*line)[i]))
			comma = false;
		else if ((*line)[i] == ',' && comma == false)
			comma = true;
		i++;
	}	
}

static void	color_getter(t_data *data, char **line, t_key id_key)
{
	int	i;
	int	j;
	int	value_color;

	handle_between_value(line);
	i = 0;
	while (i < 3)
	{
		j = 0;
		while ((*line)[j] && ft_isdigit((*line)[j]))
			j++;
		if ((*line)[j] && (*line)[j] != ',' && (*line)[j] != ' ' && (*line)[j] != '\n')
			{printf("je sors parce que jai trouve le char `%c`\n", (*line)[j]); exit (1);}
		printf("carac d'arret -> [%c]\n", (*line)[j]);
		(*line)[j] = '\0';
		printf ("passage %d : line avec le nouveau \"\\0\" -> {%s}\n",i, *line);
		value_color = ft_atoi(*line);
		if (id_key == F && data->elem.f_value[i] == -1 && value_color != -1)// check si double et si er ror du atoi (-1)
			data->elem.f_value[i] = value_color;
		else if (id_key == C && data->elem.c_value[i] == -1 && value_color != -1)
			data->elem.c_value[i] = value_color;
		else
		{printf("doublon ceiling couleur\n"); exit(1);}
		printf("value_color = {%d}\n", value_color);
		(*line) += j + 1; // avance du * jusqu'au un caractere apres le '\0' intermediaire (le +1)
		printf("carac du nouveau depart {%c}\n", **line);
		i++;
	}
}

//static void	color_getter(t_data *data, char **line, t_key id_key)
//{
//	// faudrait essayer de faire differemment je pense parce que virtuellement les fonctions
//	// floor_color() et ceiling_color() sont les memes fonctions
//	if (id_key == F)
//		return ;//floor_color(data, line);
//	else if (id_key == C)
//		ceiling_color(data, line);
//	else
//	{
//		printf("exit color_getter()\n");
//		exit (1);
//	}
//}


static void path_getter(t_data *data, char **line, t_key id_key)
{
	printf("path_getter line = `%s`", *line);

	unsigned int	n;
	char*			tmp_line;

	tmp_line = *line;
	n = 0;
	while (**line && **line != ' ' && **line != '\n')
	{
		(*line)++;
		n++;
	}
	if (!data->elem.path[id_key]) // protection pour eviter les doublons
		data->elem.path[id_key] = ft_strndup(tmp_line, n);
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
	id_key = 0;
	while (id_key <= 5)
	{
		if (key_finder(&line, id_key))
		{
			printf("found key number %d\n-------------------------\n", id_key);
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
	printf ("\n\n||||| Elem values after data->elem.e_counter == 6 |||||\n\n");
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
