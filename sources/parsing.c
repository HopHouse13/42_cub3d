/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:33:57 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/10 13:13:24 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// static void	check_filename(argv)
// {
// 	int	i;

// 	i = 0;

// }

void	check_file(char *argv)
{
	(void) argv;
	int	n;

	n = ft_strlen(argv) - 4;
	if (!ft_strncmp(argv, ".cub", ft_strlen(argv) - 4))
		printf("bon format\n");
	else
		printf("mauvais format\n");
	// check_filename(argv);


}