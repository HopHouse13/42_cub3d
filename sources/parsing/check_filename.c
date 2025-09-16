/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:42:52 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/16 15:46:36 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	check_filename(t_data *data, char *mapfile)
{
	size_t	n;

	n = ft_strlen(mapfile);
	if (n <= 4)
		exit_door(data, "Filename too short", ERROR);

	if (!valid_ext(mapfile, ".cub", n - 4))
		exit_door(data, "Invalid extension name", ERROR);
}