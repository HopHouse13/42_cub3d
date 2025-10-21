/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 14:31:29 by pbret             #+#    #+#             */
/*   Updated: 2025/10/21 13:38:39 by pbret            ###   ########.fr       */
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
}

// une valeur dans le format RGB doit etre comprise entre o et 255 (1 octet)
static void	check_value(t_cub *cub, int color_value)
{
	if (color_value > 255 || color_value < 0)
		exit_door(cub, PSG_RGB_FT_ERR, ft_itoa(color_value));
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
// [nb_colors > 1], on est a la derniere sequence; seul char autorise [ ]
// * Il faut exatement une virgule entre les sequences; faut ignorer ce controle
// pour la derniere sequence.
// return l'indexe du nouveau depart de la porchaine valeur.
static int	between_value(t_cub *cub, int nb_colors, char **line)
{
	int		i;
	int		comma;

	i = 0;
	comma = 0;
	while ((*line)[i] && ft_isdigit((*line)[i]))
		i++;
	if (i == 0 && !ft_isdigit((*line)[i]))
		exit_door(cub, PSG_RGB_FT_ERR, *line);
	while ((*line)[i] && !ft_isdigit((*line)[i]))
	{	
		if (((*line)[i] != ',' && (*line)[i] != ' ' && (*line)[i] != '\n')
			|| (nb_colors > 1 && (*line)[i] != ' ' && (*line)[i] != '\n'))
			exit_door(cub, PSG_RGB_FT_ERR, *line);
		else if ((*line)[i] == ',')
			comma++;
		i++;
	}
	if (comma != 1 && nb_colors < 2)
		exit_door(cub, PSG_RGB_FT_ERR, *line);
	return (i);
}

// check les espaces entre chaque valeur(between_value)
// check valeurs(check_value)
// check doublon(if la fin)
// 'nb_char_value' qui est indentifiee par 'between_value' est
// le nombre de char de la valeur.
// substr pour isoler la valeur pour atoi.
// free de tmp_char_value.
// Apres le atoi et le stockage de la valeur, deplacement du pointeur vers
// le premier char du prochain digit pour recommencer le proccess de la boucle
// pour chaque valeur.
// le pointeur line est avance jusqu'a la prochaine value avec nb_char_value
// check_value puis stockage des valeurs dans deux tableau de int.
static void	get_color(t_cub *cub, int *loc_value, char **line, int idx)
{
	int		value_color;
	int		nb_char_value;

	nb_char_value = between_value(cub, idx, line);
	value_color = ft_atoi(*line);
	check_value(cub, value_color);
	if (*loc_value == -1)
		*loc_value = value_color;
	else
		exit_door(cub, PSG_DUP_COLOR_ERR, *line);
	(*line) += nb_char_value;
}

// Le pointeur vers le 1er char qui n'est pas un espace.
// Check si ce char est bien un chiffre.
// Boucle pour avancer 'idx' qui est l'index des deux tab de int
// (stockage des valeurs)
// Sortie de boucle, conversion des couleurs en un int. (bit shifting)
void	handle_colors(t_cub *cub, char **line, t_key key_id)
{
	int		idx;

	if (!ft_isdigit(**line))
		exit_door(cub, PSG_RGB_FT_ERR, *line);
	idx = -1;
	while (++idx < 3)
	{
		if (key_id == F)
			get_color(cub, &cub->elem.f_values[idx], line, idx);
		else
			get_color(cub, &cub->elem.c_values[idx], line, idx);
	}
	color_conversion(cub);
}
