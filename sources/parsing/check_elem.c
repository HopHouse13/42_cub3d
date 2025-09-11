/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:43:41 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/10 15:47:34 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// boucle
// lexture gnl
void	check_elem(char *argv)
{
	int	fd;
	char* line;

	line = NULL;
	// fd -1; // pas sur que se soit utile 
	fd = open("./maps/invalid_maps/bad_elem1.cub", O_RDONLY);
	if (fd < 0)
		{printf("message pprobleme d'ouverture du .cub\n"), exit(1);}
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
}
