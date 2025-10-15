/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:42:52 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/15 15:23:12 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	check_access(t_cub *cub, char *map)
{
	int		tmp_fd;
	int		tmp_read;
	char	tmp_buf[1];

	tmp_fd = open(map, O_RDONLY);
	if (tmp_fd == -1)
		exit_door(cub, PSG_OPEN_FILE_ERR);
	tmp_read = read(tmp_fd, tmp_buf, 1);
	if (tmp_read == -1)
	{
		close(tmp_fd);
		exit_door(cub, PSG_READ_FILE_ERR);
	}
}

// Compare les 4 derniers char du nom du fichier avec "".cub".
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

// check si le nom du fichier excite (supperieur a 4 char) et si
// c'est la bonne extention.
void	check_filename(t_cub *cub, char *mapfile)
{
	size_t	n;

	n = ft_strlen(mapfile);
	if (n <= 4 || !valid_ext(mapfile, ".cub", n - 4))
		exit_door(cub, PSG_FILENAME_ERR);
	check_access(cub, mapfile);
}
