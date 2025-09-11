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
	printf("Into check_elem\n");
	int	fd;
	
	fd -1; // pas sur que se soit utile 
	fd = open("./maps/invalid_maps/bad_elem1.cub", O_RDONLY);
	if (!fd)
		{printf("message pprobleme d'ouverture du .cub\n"), exit(1);}
}
