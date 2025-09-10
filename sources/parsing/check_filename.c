/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:42:52 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/10 15:43:12 by tjacquel         ###   ########.fr       */
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

void	check_filename(char *argv)
{
	size_t	n;

	n = ft_strlen(argv);
	if (n <= 4)
		exit(1); // fonction sortie mess
	if (!valid_ext(argv, ".cub", n - 4))
		exit(1); // fonction sortie mess
}