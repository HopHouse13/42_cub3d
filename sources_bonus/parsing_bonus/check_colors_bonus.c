/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 14:31:29 by pbret             #+#    #+#             */
/*   Updated: 2025/10/23 00:46:29 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

// Convert RGB format (3 values) into an int using bit shifting.
// An int is composed of 4 bytes; the leftmost byte is the most significant.
// The 1st byte is unused (possibly for transparency).
// The 2nd byte is used for RED.
// The 3rd byte is used for GREEN.
// The 4th byte is used for BLUE.
static void	color_conversion(t_cub *cub)
{
	if (cub->elem.f_values[0] != -1)
	{
		cub->elem.f_color = (((cub->elem.f_values[0] & 0xFF) << 16)
				| ((cub->elem.f_values[1] & 0xFF) << 8)
				| (cub->elem.f_values[2] & 0xFF));
	}
	if (cub->elem.c_values[0] != -1)
	{
		cub->elem.c_color = (((cub->elem.c_values[0] & 0xFF) << 16)
				| ((cub->elem.c_values[1] & 0xFF) << 8)
				| (cub->elem.c_values[2] & 0xFF));
	}
}

// A value in RGB format must be between 0 and 255 (1 byte).
static void	check_value(t_cub *cub, int color_value)
{
	if (color_value < 0)
		exit_door(cub, PSG_OVERFLOW_ERR, NULL);
	if (color_value > 255)
		exit_door(cub, PSG_RGB_FT_ERR, NULL);
}

// Function for moving the pointer, checking conformity, and transmitting
// information.
// Works by sequence: a sequence = value + the separator after it.
// Example:
// line[F 1, 22, t333] -> sequence 1 [1, ]; sequence 2 [22, t]; sequence 3 [333]
// Steps for each sequence:
// 1. Count the number of digits.
// 2. Store the length of the digits.
// 3. Move to the next digit while checking conformity.
// 4. Place '\0' at the end of the digit series for atoi.
// Note: no pointer is actually moved here.
// ---
// * tmp_end stores the index of the character following the last digit of
//   the value, so it can be replaced with '\0' to stop ft_atoi.
// * The first two sequences: allowed characters are [,][ ][\n].
// * For [nb_colors > 1], we are at the last sequence;
//   only allowed character is [ ].
// * There must be exactly one comma between sequences; ignore this check for
//   the last sequence.
// Returns the index of the new starting position for the next value.

static int	between_value(t_cub *cub, int nb_colors, char **line)
{
	int		i;
	int		comma;
	int		tmp_end;

	i = 0;
	comma = 0;
	while ((*line)[i] && ft_isdigit((*line)[i]))
		i++;
	if (i == 0 && !ft_isdigit((*line)[i]))
		exit_door(cub, PSG_RGB_FT_ERR, *line);
	tmp_end = i;
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

// Check the spaces between each value (between_value).
// Check the values themselves (check_value).
// Check for duplicates (at the end).
// 'nb_char_value', identified by 'between_value', is the number of characters
//  in the value.
// Use substr to isolate the value for atoi.
// Free the temporary string tmp_char_value.
// After atoi and storing the value, move the pointer to the first character
// of the next digit to repeat the loop for each value.
// The line pointer is advanced to the next value using nb_char_value.
// Check the value again and store the values in two int arrays.

static void	get_color(t_cub *cub, int *loc_value, char **line, int idx)
{
	int		color_value;
	int		nb_char_value;

	nb_char_value = between_value(cub, idx, line);
	color_value = ft_atoi(*line);
	check_value(cub, color_value);
	if (*loc_value == -1)
		*loc_value = color_value;
	else
		exit_door(cub, PSG_DUP_COLOR_ERR, *line);
	(*line) += nb_char_value;
}

// Pointer to the first non-space character.
// Check if this character is a valid digit.
// Loop to advance 'idx', which is the index of the two int arrays
// (for storing values).
// After the loop, convert the colors into an int using bit shifting.
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
