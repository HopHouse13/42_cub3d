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

static t_error check_color(t_cub *cub)
{//printf("\n||||| CHECK COLORS VALUES |||||\n");
	int	i;
	i = 0;
	if (cub->elem.f_values[0])
	{
		while (i < 3)
		{
			if (cub->elem.f_values[i] > 255 || cub->elem.f_values[i] < 0) // peux etre egale a -1 si une valeurs depasse les limites de INT (retour atoi)
				return (E_VALUE_COLOR);
			i++;
		}
	}
	if (cub->elem.c_values[0])
	{
		while (++i < 3)
		{
			if (cub->elem.c_values[i] > 255 || cub->elem.c_values[i] < 0)
				return (E_VALUE_COLOR);
			i++;
		}
	}
	return (OK);
}

static t_error	check_path(char *path)
{//printf("\n||||| CHECK RIGHTS PATH |||||\n");
	int		tmp_fd;
	int		tmp_read;
	char	tmp_buf[1]; // pas sur que ca passe la norme

	tmp_fd = open(path, O_RDONLY);
	if (tmp_fd == -1)
		return (E_PATH);
	tmp_read = read(tmp_fd, tmp_buf, 1);
	if (tmp_read == -1) // si le path est un repertoire, le fd va etre initialise mais nous ne pourons pas lire le dossier -> read retourne -1 si il n'arrive pas a lire
		return (E_READ_PATH);
	close(tmp_fd); // si besoin des fd pour l'exec, on pourra les stocker dans une struct ici. Au lieu de les fermer.
	return (OK);
}

static t_error	check_rest_of_line(char **line)
{
	while(**line && **line != '\n')
	{
		if (**line != ' ')
			return (E_LINE_FT);
		(*line)++;
	}
	return (OK);
}

// fonction de deplacement, controle de la conformitee et transmettre les infos
// Fonctionne par sequence: une sequence = valeur + l'entre deux d'apres
// line [F 1, 22, t 333] -> sequence 1 [1, ]; sequence 2 [22, t ]; sequence 3 [333]
// Etape pour chaque sequence: 
// 1 [comptabiliser nb digits]
// 2 [stocker la len des digits]
// 3 [se deplacer jusqu'au prochain digit tout en controlant la conformitee]
// 4 [placer '\0' a la fin de la serie de digits pour l'atoi]
// Rappel : aucun pointeur est deplacer ici.
static t_error	between_value(char **line, int nb_color_found, int *new_start)
{
	int	i;
	int	comma;
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
			return (E_RGB_FT);
		else if ((*line)[i] == ',')
			comma++;
		i++;
	}
	if (comma != 1 && nb_color_found < 2) // il faut exatement une virgule entre les sequences; faut ignorer ce controle pour la derniere sequence
		return (E_RGB_FT);
	(*line)[tmp_end] = '\0'; // remplacement du char apres la serie de digits par '\0'
	*new_start = i;
	return (OK); // retourne l'indexe ou je trouve le prochain digit
}

static void	color_conversion(t_cub *cub)
{
	if (cub->elem.f_values[0])
	{
	cub->elem.f_color = (((cub->elem.f_values[0] & 0xFF) << 16)
							| ((cub->elem.f_values[1] & 0xFF) << 8)
							| (cub->elem.f_values[2] & 0xFF));
	}
	if (cub->elem.c_values[0])
	{
	cub->elem.c_color = (((cub->elem.c_values[0] & 0xFF) << 16)
							| ((cub->elem.c_values[1] & 0xFF) << 8)
							| (cub->elem.c_values[2] & 0xFF));
	}
	return ;
}

static t_error	handle_colors(t_cub *cub, char **line, t_key key_id)
{
	int			i;
	int			value_color;
	int			new_start;
	int			err_id;

	if (!ft_isdigit(**line)) // je dois commencer avec un digit car complexe de l'integrer dans le process std
		return (E_RGB_FT);
	i = -1;
	while (++i < 3)
	{
		err_id = between_value(line, i, &new_start);// retourne le nb de deplacement pour aller jusqu'a la prochaine digit
		if (err_id != OK)
			return (err_id);
		//printf("sous chaine valeur [%s]\n", *line);
		value_color = ft_atoi(*line);
		if (key_id == F && cub->elem.f_values[i] == -1) // check si double. / si atoi renvoit -1 -> verificatoin plus tard
			cub->elem.f_values[i] = value_color;
		else if (key_id == C && cub->elem.c_values[i] == -1)
			cub->elem.c_values[i] = value_color;
		else
			return (E_DUP_COLOR);
		(*line) += new_start; // apres le atoi, deplacement du pointeur vers le debut de la prochaine serie de digits
	}
	err_id = check_color(cub);
	if (err_id != OK)
		return (err_id);
	color_conversion(cub);
	return (OK);
}

static t_error handle_paths(t_cub *cub, char **line, t_key key_id)
{
	//printf("handle_paths line = `%s`", *line);
	unsigned int	n;
	char*			tmp_line;

	tmp_line = *line;
	n = 0;
	while (**line && **line != ' ' && **line != '\n')
	{
		(*line)++;
		n++;
	}
	if (!cub->elem.path[key_id]) // protection pour eviter les doublons
	{
		cub->elem.path[key_id] = ft_strndup(tmp_line, n);
		if (!cub->elem.path[key_id])
			return (E_ALLOC);
	}
	else
		return (E_DUP_PATH);
	return (check_path(cub->elem.path[key_id]));
}

static t_error	handle_get_elem(t_cub *cub, char **line, t_key key_id)
{
	t_error	err_id;

	err_id = OK;
	while (**line && **line == ' ')
		(*line)++;
	if (key_id < F)
		err_id = handle_paths(cub, line, key_id);
	else
		err_id = handle_colors(cub, line, key_id);
	return (err_id);
}

static bool	key_finder(char **line, t_key key_id)
{
	static const char	*tab_keys[6] = {"NO ", "EA ", "SO ", "WE ", "F ", "C "};

	if ((key_id < F && !ft_strncmp(*line, tab_keys[key_id], 3))
		|| (key_id > WE && !ft_strncmp(*line, tab_keys[key_id], 2)))
	{
		if (key_id < F)
			*line += 3;
		else
			*line += 2;
		return (true);
	}
	return (false);
}

static t_error	handle_line(t_cub *cub, char *line)
{
	t_key	key_id;
	t_error	err_id;

	err_id = OK;
	while (*line && *line == ' ') // les premiers espaces
		line++;
	if (*line == '\n' || *line == '\0') // passe la line suivante si la line est remplit que d'[ ] et un [\n]
		return (OK);
	key_id = NO;
	while (key_id <= C)
	{
		if (key_finder(&line, key_id))
		{
			//printf("found key number %d\n-------------------------\n", key_id);
			cub->elem.e_counter++;
			err_id = handle_get_elem(cub, &line, key_id);
			if (err_id == OK)
				err_id = check_rest_of_line(&line);
			return (err_id);
		}
		key_id++;
	}
	return (E_NO_KEY);
}

void	check_elem(t_cub *cub, char *mapfile)
{
	char 	*line;
	t_error	err_id;

	err_id = OK; // initialise la variable a ok par defaut
	cub->fd_file = open(mapfile, O_RDONLY);
	if (cub->fd_file < 0)
		exit_door(cub, E_OPEN_FILE);
	while (cub->elem.e_counter < 6) // si les 6 parametres ont ete trouves, on passe a la suite
	{
		line = get_next_line(cub->fd_file, &err_id, false);
		if (err_id == E_ALLOC) // erreur malloc
			exit_door(cub, err_id);
		if (!line) // fin de file
			exit_door(cub, E_MISS_PARAM);
		//printf("\n||||| NOUVELLE LINE |||||\nNEW LINE : [%s]\n", line);
		err_id = handle_line(cub, line);
		free(line);
		//printf("value_err_id : [%d]\n", err_id);
		if(err_id > OK)
			exit_door(cub, err_id);
	}
	//printf ("\n\n||||| Elem values after cub->elem.e_counter == 6 |||||\n\n");
	//print_elem(&cub->elem);
	check_color(cub);
}

// TO DO -
// handle_colors ✅
// LIGNES VIDES (*avec ou sans espaces) ✅
// check le path (check_path) - sil est valide, sil existe, si les droits sont bons etc. ✅
// check la couleur (check_color) - si c'est bien [0-255] ✅
// check_map
// gestion des free de tout  (des strndup et du gnl)
// message d'erreur ✅ et free checker ce quil y a free etc.
