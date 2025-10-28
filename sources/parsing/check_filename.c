/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:42:52 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/28 18:08:06 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Check if the map file can be opened and read; exit on failure.
static void	check_access(t_cub *cub, char *map)
{
	char	tmp_buf[1];

	cub->psg.tmp_fd = open(map, O_RDONLY);
	if (cub->psg.tmp_fd == -1)
		exit_door(cub, PSG_OPEN_FILE_ERR, map);
	cub->psg.tmp_read = read(cub->psg.tmp_fd, tmp_buf, 1);
	if (cub->psg.tmp_read == -1)
		exit_door(cub, PSG_READ_FILE_ERR, map);
}

// Compare the last 4 characters of the file name with ".cub".
static bool	valid_ext(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[n] && s2[i])
	{
		if (s1[n] != s2[i])
			return (false);
		i++;
		n++;
	}
	return (true);
}

// Check if the file name is valid (longer than 5 characters).
// Ensure it has the correct ".cub" extension and that there is no '/' 
// right before it.
// If there is a '/', it means the file name is missing.
void	check_filename(t_cub *cub, char *mapfile)
{
	size_t	n;

	n = ft_strlen(mapfile);
	if (n <= 5 || !valid_ext(mapfile, ".cub", n - 4) || mapfile[n - 5] == '/')
		exit_door(cub, PSG_FILENAME_ERR, mapfile);
	check_access(cub, mapfile);
}
