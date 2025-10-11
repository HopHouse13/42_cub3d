/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 14:31:29 by pbret             #+#    #+#             */
/*   Updated: 2025/10/11 15:54:31 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Conversion du format RGB (3 valeurs) en un int avec du bit shifting.
// Un int est compose de 4 octets, l'octet le plus a gauche visuellement est le 
// plus significatif.
// Le 1er n'est pas utliser (peut etre utilise pour la transparence)
// Le 2eme est utilise pour le RED
// Le 3eme est utilise pour le GREEN
// Le 4eme est utilise pour le BLUE
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

// une valeur dans le format RGB doit etre comprise entre o et 255 (1 octet)
static t_error	check_color(int color_value)
{
	if (color_value > 255 || color_value < 0)
		return (E_VALUE_COLOR);
	return (OK);
}

// fonction de deplacement, controle de la conformitee et transmettre les infos
// Fonctionne par sequence: une sequence = valeur + l'entre deux d'apres
// line[F 1, 22, t333] -> sequence 1 [1, ]; sequence 2 [22, t]; sequence 3 [333]
// Etape pour chaque sequence: 
// 1 [comptabiliser nb digits]
// 2 [stocker la len des digits]
// 3 [se deplacer jusqu'au prochain digit tout en controlant la conformitee]
// 4 [placer '\0' a la fin de la serie de digits pour l'atoi]
// Rappel : aucun pointeur est deplacer ici.
// ---
// * tmp_end prend l'index du char suivant du dermier digit de la valeur pour
// pourvoir remplacer la vleur de ce pointeur par '\0' pour arrter le ft_atoi.
// * Les 2 premieres sequences ->  char autorises [,][ ][\n].
// [nb_color_found > 1], on est a la derniere sequence; seul char autorise [ ]
// * Il faut exatement une virgule entre les sequences; faut ignorer ce controle
// pour la derniere sequence.
static t_error	between_value(char **line, int nb_color_found, int *new_start)
{
	int	i;
	int	comma;
	int	tmp_end;

	i = 0;
	comma = 0;
	while ((*line)[i] && ft_isdigit((*line)[i]))
		i++;
	if (i == 0 && !ft_isdigit((*line)[i]))
		return (E_RGB_FT);
	tmp_end = i;
	while ((*line)[i] && !ft_isdigit((*line)[i]))
	{	
		if (((*line)[i] != ',' && (*line)[i] != ' ' && (*line)[i] != '\n')
			|| (nb_color_found > 1 && (*line)[i] != ' ' && (*line)[i] != '\n'))
			return (E_RGB_FT);
		else if ((*line)[i] == ',')
			comma++;
		i++;
	}
	if (comma != 1 && nb_color_found < 2)
		return (E_RGB_FT);
	(*line)[tmp_end] = '\0';
	*new_start = i;
	return (OK);
}

// check les espaces entre chaque valeur(between_value)
// check valeurs(check_color)
// check doublon(if la fin)
// 'new_start' qui est indentifiee par 'between_value' est
// l'index du 1er char de chaque nouvelle valeur.
// Apres le atoi et le stockage de la valeur, deplacement du pointeur vers
// le premier char du prochain digit pour recommencer le proccess de la boucle
// pour chaque valeur.
// 'between_value' remplace le char apres le dernier digit de la valeur traitee
// par '\0' pour que ft_atoi s'arrete a la fin de la valeur.
// check_color puis stockage des valeurs dans deux tableau de int.
static t_error	handle_color_value(int *location_value, char **line, int idx)
{
	int		value_color;
	int		new_start;
	t_error	err_id;

	err_id = between_value(line, idx, &new_start);
	if (err_id != OK)
		return (err_id);
	value_color = ft_atoi(*line);
	err_id = check_color(value_color);
	if (err_id != OK)
		return (err_id);
	if (*location_value == -1)
		*location_value = value_color;
	else
		return (E_DUP_COLOR);
	(*line) += new_start;
	return (OK);
}

// Le pointeur vers le 1er char qui n'est pas un espace.
// Check si ce char est bien un chiffre.
// Boucle pour avancer 'idx' qui est l'index des deux tab de int
// (stockage des valeurs)
// Sortie de boucle, conversion des couleurs en un int. (bit shifting)
t_error	handle_colors(t_cub *cub, char **line, t_key key_id)
{
	int		idx;
	t_error	err_id;

	if (!ft_isdigit(**line))
		return (E_RGB_FT);
	idx = -1;
	while (++idx < 3)
	{
		if (key_id == F)
			err_id = handle_color_value(&cub->elem.f_values[idx], line, idx);
		else
			err_id = handle_color_value(&cub->elem.c_values[idx], line, idx);
		if (err_id != OK)
			return (err_id);
	}
	color_conversion(cub);
	return (OK);
}
