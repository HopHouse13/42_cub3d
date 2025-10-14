/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:42:52 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/14 18:18:52 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
}
