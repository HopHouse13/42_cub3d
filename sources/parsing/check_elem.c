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

// check si il y a qutre chose que des espace apres le path ou la couleur.
static t_error	check_rest_of_line(char **line)
{
	while (**line && **line != '\n')
	{
		if (**line != ' ')
			return (PSG_LINE_FT_ERR);
		(*line)++;
	}
	return (OK);
}

// Avance jusqu'a 1er char qui n'est pas un espace.
// dispatch en fonction de la keu trouvee.
// En de F(4) c'est un path sinon c'est une couleur.
// voir Enum struct
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

// init un tab avec les 6 key avec leurs valeurs de la struct ENUM
// on compare la key trouvee avec les 6 key
// si c'est une key de texture on avant de 3 le pointeur de line
// si couleur -> avance de 2
// resturn bool si oui ou non on a trouve une key
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

// skip des espaces et la lignes vide
// initialisation de key_id a la premiere valeur de l'enum (NO)
// key trouvee avec 'key_finder', on la check et stockavec 'handle_get_elem.
// si cette fonction renvoye une erreur, on return l'erreur.
// si apres il y a des char invalid apres tout se processus, return l'erreur.
static t_error	handle_line(t_cub *cub, char *line)
{
	t_key	key_id;
	t_error	err_id;

	err_id = OK;
	while (*line && *line == ' ')
		line++;
	if (*line == '\n' || *line == '\0')
		return (OK);
	key_id = NO;
	while (key_id <= C)
	{
		if (key_finder(&line, key_id))
		{
			cub->elem.e_counter++;
			err_id = handle_get_elem(cub, &line, key_id);
			if (err_id == OK)
				err_id = check_rest_of_line(&line);
			return (err_id);
		}
		key_id++;
	}
	return (PSG_NO_KEY_ERR);
}

// ouvre le .cub
// loop -> lecture continue tant que pas trouve 6 elem (4 patchs + 2 colors)
// les messages des erreurs de check_elem sont le retour de handle_line,
// stock dans err_id.
// si on arrive a la fin du file sans avoir avoir trouve els 6 elem -> error
void	check_elem(t_cub *cub, char *mapfile)
{
	char	*line;
	t_error	err_id;

	err_id = OK;
	cub->fd_file = open(mapfile, O_RDONLY);
	if (cub->fd_file < 0)
		exit_door(cub, PSG_OPEN_FILE_ERR, mapfile);
	while (cub->elem.e_counter < 6)
	{
		line = get_next_line(cub->fd_file, &err_id, false);
		if (err_id == PSG_ALLOC_ERR)
			exit_door(cub, err_id, NULL);
		if (!line)
			exit_door(cub, PSG_MISS_PARAM_ERR, NULL);
		err_id = handle_line(cub, line);
		free(line);
		if (err_id > OK)
			exit_door(cub, err_id, NULL);
	}
}
