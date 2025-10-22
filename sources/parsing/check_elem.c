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

// check si il y a autre chose que des espace apres le path ou la couleur.
static void	check_rest_of_line(t_cub *cub, char **line)
{
	while (**line && **line != '\n')
	{
		if (**line != ' ')
			exit_door(cub, PSG_LINE_FT_ERR, *line);
		(*line)++;
	}
}

// Avance jusqu'a 1er char qui n'est pas un espace.
// dispatch en fonction de la keu trouvee.
// En de F(4) c'est un path sinon c'est une couleur.
// voir Enum struct
static void	handle_get_elem(t_cub *cub, char **line, t_key key_id)
{
	while (**line && **line == ' ')
		(*line)++;
	if (key_id < F)
		handle_paths(cub, line, key_id);
	else
		handle_colors(cub, line, key_id);
}

// init un tab avec les 6 key avec leurs valeurs de la struct ENUM
// on compare la key trouvee avec les 6 key
// si c'est une key de texture on avant de 3 le pointeur de line
// si couleur -> avance de 2
// resturn bool si oui ou non on a trouve une key
static bool	key_finder(char **line, t_key key_id)
{
	static const char	*tab_keys[17] = {"NO ", "EA ", "SO ", "WE ", "DO ",
		"s0 ", "s1 ", "s2 ", "s3 ", "s4 ", "s5 ",
		"s6 ", "s7 ", "s8 ", "s9 ", "F ", "C "};

	if ((key_id < F && !ft_strncmp(*line, tab_keys[key_id], 3))
		|| (key_id > s9 && !ft_strncmp(*line, tab_keys[key_id], 2)))
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
// Apres check si il y a des char invalid apres tout se processus.
static void	handle_line(t_cub *cub, char *line)
{
	t_key	key_id;

	while (*line && *line == ' ')
		line++;
	if (*line == '\n' || *line == '\0')
		return ;
	key_id = NO;
	while (key_id <= C)
	{
		if (key_finder(&line, key_id))
		{
			cub->elem.e_counter++;
			handle_get_elem(cub, &line, key_id);
			check_rest_of_line(cub, &line);
			return ;
		}
		key_id++;
	}
	exit_door(cub, PSG_NO_KEY_ERR, NULL);
}

// ouvre le .cub
// loop -> lecture continue tant que pas trouve 6 elem (4 patchs + 2 colors)
// Plusieurs controle sur si l'allocation.
// Handle_line prend la line stock dans la struct psg.
// Si on arrive a la fin du file sans avoir avoir trouve els 6 elem -> error
void	check_elem(t_cub *cub, char *mapfile)
{
	char	*err_id;

	err_id = OK;
	cub->psg.fd_file = open(mapfile, O_RDONLY);
	if (cub->psg.fd_file < 0)
		exit_door(cub, PSG_OPEN_FILE_ERR, NULL);
	while (cub->elem.e_counter < 17)
	{
		cub->psg.line = get_next_line(cub->psg.fd_file, &err_id, false);
		if (!ft_strcmp(err_id, PSG_ALLOC_ERR))
			exit_door(cub, err_id, NULL);
		if (!cub->psg.line)
			exit_door(cub, PSG_MISS_PARAM_ERR, NULL);
		handle_line(cub, cub->psg.line);
		free(cub->psg.line);
		cub->psg.line = NULL;
	}
}
