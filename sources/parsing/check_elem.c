/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:43:41 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/15 14:05:38 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void check_color(t_data *data)
{printf("\n||||| CHECK COLORS VALUES |||||\n");
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (data->elem.f_value[i] > 255 || data->elem.f_value[i] < 0) // peux etre egale a -1 si une valeurs depasse les limites de INT (retour atoi)
			exit_door(data, "color value hors limits", ERROR);
	}
	i = -1;
	while (++i < 3)
	{
		if (data->elem.c_value[i] > 255 || data->elem.c_value[i] < 0)
			exit_door(data, "color value hors limits", ERROR);
	}
	printf("valeurs couleurs valides\n");
}

static void check_path(t_data *data)
{printf("\n||||| CHECK RIGHTS PATH |||||\n");
	int		i;
	int		tmp_fd;
	int		tmp_read;
	char	tmp_buf[1]; // pas sur que ca passe la norme

	i = -1;
	while(++i < 4)
	{
		tmp_fd = open(data->elem.path[i], O_RDONLY);
		printf("value tmp_fd [%d]\n", tmp_fd);
		if (tmp_fd == -1)
			exit_door(data, "error lors de l'ouverture du fichier texture", ERROR);
		tmp_read = read(tmp_fd, tmp_buf, 1);
		printf("value tmp_read [%d]\n", tmp_read);
		if (tmp_read == -1) // si le path est un repertoire, le fd va etre initialise mais nous ne pourons pas lire le dossier -> read retourne -1 si il n'arrive pas a lire
			exit_door(data, "error lors de la lecture du fichier texture", ERROR);
		close(tmp_fd); // si besoin des fd pour l'exec, on pourra les stocker dans une struct ici. Au lieu de les fermer.
	}
	printf("Fichiers textures valides\n");
}

static void	check_rest_of_line(t_data *data, char **line)
{
	while(**line && **line != '\n')
	{
		if (**line != ' ')
			exit_door(data, "caractere(s) apres les paths ou les color_valeurs", ERROR);
		(*line)++;
	}
}
// ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ FT_TOTO ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ

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
//		if (**line == ',' && i != 2) // je veux etre certain de pas skip un ',' en fin de RGB par exemple F 250,225,175
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

// ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ FT_TOTO ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ-ˆ

// fonction de deplacement, controle de la conformitee et transmettre les infos
// Fonctionne par sequence: une sequence = valeur + l'entre deux d'apres
// line [F 1, 22, t 333] -> sequence 1 [1, ]; sequence 2 [22, t ]; sequence 3 [333]
// Etape pour chaque sequence: 
// 1 [comptabiliser nb digits]
// 2 [stocker la len des digits]
// 3 [se deplacer jusqu'au prochain digit tout en controlant la conformitee]
// 4 [placer '\0' a la fin de la serie de digits pour l'atoi]
// Rappel : aucun pointeur est deplacer ici.
static int	handle_between_value(t_data *data, char **line, int nb_color_found)
{
	int	i;
	int comma;
	int	tmp_end;

	i = 0;
	comma = 0;
	while ((*line)[i] && ft_isdigit((*line)[i]))
		i++;
	tmp_end = i; // stock la position de fin de serie des digits
	while ((*line)[i] && !ft_isdigit((*line)[i])) // gestion des char entre deux series de digits
	{	
		if (((*line)[i] != ',' && (*line)[i] != ' ' && (*line)[i] != '\n') // les 2 premieres sequences ->  char autorises [,][ ][\n]
			|| (nb_color_found > 1 && (*line)[i] != ' ' && (*line)[i] != '\n')) // [nb_color_found > 1] -> on est a la 3eme et derniere sequence; char autorise [ ]
			exit_door(data, "je sors parce que jai trouve un char invalide", ERROR);
		else if ((*line)[i] == ',')
			comma++;
		i++;
	}
	printf("value_comma : %d\n", comma);
	printf("nb_color_found : %d\n", nb_color_found);
	if (comma < 1 && nb_color_found < 2) // il faut exatement une virgule entre les sequences; faut ignorer ce controle pour la derniere sequence
		exit_door(data, "manque 1 virgule entre 2 valeurs", ERROR);
	else if (comma > 1 && nb_color_found < 2)
		exit_door(data, "manque 1 valeur entre 2 virgule", ERROR);
	(*line)[tmp_end] = '\0'; // remplacement du char apresla serie de digits par '\0'
	return (i); // retourne l'indexe ou je trouve le prochain digit
}

static void	color_getter(t_data *data, char **line, t_key id_key)
{
	int	i;
	int	value_color;
	int	tmp_end;

	if (!ft_isdigit(**line)) // je dois commencer avec un digit car complexe de l'integrer dans le process std
		exit_door(data, "1er char non digit", ERROR);
	i = 0;
	while (i < 3)
	{
		tmp_end = handle_between_value(data, line, i);// retourne le nb de deplacement pour aller jusqu'a la prochaine digit
		value_color = ft_atoi(*line);
		if (id_key == F && data->elem.f_value[i] == -1) // check si double. si atoi renvoit -1 -> verificatoin plus tard
			data->elem.f_value[i] = value_color;
		else if (id_key == C && data->elem.c_value[i] == -1)
			data->elem.c_value[i] = value_color;
		else
			exit_door(data, "doublon couleur ou error lors du atoi(limites)", ERROR);
		printf("value_color = {%d}\n\n", value_color);
		(*line) += tmp_end; // apres le atoi, deplacement du pointeur vers le debut de la prochaine serie de digits
		printf("carac du nouveau depart {%c}\n", **line);
		i++;
	}
}

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
		exit_door(data, "doublon path", ERROR);
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

static void	handle_line(t_data *data, char *line)
{
	t_key	id_key;

	while (*line && *line == ' ') // les premiers espaces
		line++;
	if (*line == '\n' || *line == '\0') // passe la line suivante si la line est remplit que d'[ ] et un [\n]
		return ;
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
			check_rest_of_line(data, &line);
			return ;
		}
		id_key++;
	}
	exit_door(data, "pas trouve de key", ERROR);
}

void	check_elem(t_data *data, char *mapfile)
{
	char	*line;

	data->fd_file = open(mapfile, O_RDONLY);
	if (data->fd_file < 0)
		exit_door(data, "message probleme d'ouverture du .cub", ERROR);
	while (data->elem.e_counter < 6 && (line = get_next_line(data->fd_file))) // si les 6 parametres ont ete trouves, on passe a la suite
	{
		printf("\n||||| NOUVELLE LINE |||||\nPRINT LINE : [%s]\n", line);
		handle_line(data, line);
		free(line);
	}
	if (data->elem.e_counter < 6)
		exit_door(data, "Parametres incomplets", ERROR);
	printf ("\n\n||||| Elem values after data->elem.e_counter == 6 |||||\n\n");
	print_elem(&data->elem);
	check_path(data);
	check_color(data);
}

//void	check_elem(t_data *data, char *mapfile)
//{
//	char	*line;

//	data->fd_file = open(mapfile, O_RDONLY);
//	if (data->fd_file < 0)
//		exit_door(data, "message probleme d'ouverture du .cub", ERROR);
//	while (data->elem.e_counter < 6) // si les 6 parametres ont ete trouves, on passe a la suite
//	{
//		printf("\n||||| NOUVELLE LINE |||||\nPRINT LINE : [%s]\n", line);
//		line = get_next_line(data->fd_file);
//		if (!line)
//			exit_door(data, "error malloc gnl", ERROR);
//		if (*line == '\0' && data->elem.e_counter < 6)
//		{
//			free(line);
//			exit_door(data, "Parametres incomplets", ERROR);
//		}
//		handle_line(data, line);
//		free(line);
//	}
//	printf ("\n\n||||| Elem values after data->elem.e_counter == 6 |||||\n\n");
//	print_elem(&data->elem);
//	check_path(data);
//	check_color(data);
//}

// TO DO -
// COLOR_GETTER ✅
// LIGNES VIDES (*avec ou sans espaces) ✅
// check le path (check_path) - sil est valide, sil existe, si les droits sont bons etc. ✅
// check la couleur (check_color) - si c'est bien [0-255] ✅
// check_map
// gestion des free de tout  (des strndup et du gnl)
// message d'erreur ✅ et free checker ce quil y a free etc.
