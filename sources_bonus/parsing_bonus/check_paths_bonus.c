/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 14:31:58 by pbret             #+#    #+#             */
/*   Updated: 2025/10/23 00:46:29 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

// Check if the path file can be opened (create a file descriptor)
// and read to verify that the file is not a directory.
// Reading with 'read' will fail (return -1) if it is a directory.
static void	check_path(t_cub *cub, char *path)
{
	int		tmp_fd;
	int		tmp_read;
	char	tmp_buf[1];

	tmp_fd = open(path, O_RDONLY);
	if (tmp_fd == -1)
		exit_door(cub, PSG_PATH_ERR, path);
	tmp_read = read(tmp_fd, tmp_buf, 1);
	if (tmp_read == -1)
		exit_door(cub, PSG_READ_PATH_ERR, path);
	close(tmp_fd);
}

// The line pointer is at the beginning of the path.
// 'nb_char_path' is the number of characters in the path to duplicate
// it correctly.
// Check if the memory reserved for the path of each specific 'key_id' is empty
// or already filled (duplicate check).
// Duplicate and store it in cub->elem.path with the specific key.
// Finally, return the result of 'check_path', which verifies if the path
// is valid.
void	handle_paths(t_cub *cub, char **line, t_key key_id)
{
	unsigned int	nb_char_path;
	char			*tmp_line;

	tmp_line = *line;
	nb_char_path = 0;
	while (**line && **line != ' ' && **line != '\n')
	{
		(*line)++;
		nb_char_path++;
	}
	if (!cub->elem.path[key_id])
	{
		cub->elem.path[key_id] = ft_strndup(tmp_line, nb_char_path);
		if (!cub->elem.path[key_id])
			exit_door(cub, ALLOC_ERR, NULL);
	}
	else
		exit_door(cub, PSG_DUP_PATH_ERR, cub->elem.path[key_id]);
	check_path(cub, cub->elem.path[key_id]);
}
