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

// Check if there is anything other than spaces after the path or color.
static void	check_rest_of_line(t_cub *cub, char **line)
{
	while (**line && **line != '\n')
	{
		if (**line != ' ')
			exit_door(cub, PSG_LINE_FT_ERR, *line);
		(*line)++;
	}
}

// Advance to the first non-space character.
// Dispatch processing based on the found key.
// If F(4), it is a path; otherwise, it is a color.
// See the Enum struct for reference.
static void	handle_get_elem(t_cub *cub, char **line, t_key key_id)
{
	while (**line && **line == ' ')
		(*line)++;
	if (key_id < F)
		handle_paths(cub, line, key_id);
	else
		handle_colors(cub, line, key_id);
}

// Initialize an array with all keys and their corresponding enum values.
// Compare the found key with all keys.
// If it's a texture key, advance the line pointer by 3.
// If it's a color key, advance by 2.
// Return a boolean indicating whether a key was found or not.
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

// Skip spaces and empty lines.
// Initialize key_id to the first value of the enum (NO).
// Key is found using 'key_finder', then checked and stored with 'handle_get_elem'.
// Afterwards, check for any invalid characters remaining after the whole process.
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

// Open the .cub file.
// Loop: read continuously until all elements are found.
// Multiple checks for memory allocation failures.
// handle_line processes the current line stored in the parsing struct.
// If the end of the file is reached without finding all elements -> error.
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
		if (!ft_strcmp(err_id, ALLOC_ERR))
			exit_door(cub, err_id, NULL);
		if (!cub->psg.line)
			exit_door(cub, PSG_MISS_PARAM_ERR, NULL);
		handle_line(cub, cub->psg.line);
		free(cub->psg.line);
		cub->psg.line = NULL;
	}
}
