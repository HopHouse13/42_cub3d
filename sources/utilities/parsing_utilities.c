/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:34:06 by pbret             #+#    #+#             */
/*   Updated: 2025/10/15 16:54:15 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Initialisation a ZERO des variables du parsing.
void	init_parsing_data(t_cub *cub)
{
	int	i;

	cub->fd_file = -1;
	cub->map.grid = NULL;
	cub->map.rows = 0;
	cub->map.max_col = 0;
	cub->player.pos.x = 0.0;
	cub->player.pos.y = 0.0;
	i = 0;
	while (i < 4)
		cub->elem.path[i++] = NULL;
	i = 0;
	while (i < 3)
	{
		cub->elem.f_values[i] = -1;
		cub->elem.c_values[i++] = -1;
	}
	cub->elem.f_color = -1;
	cub->elem.c_color = -1;
	cub->elem.facing = 0;
	cub->elem.start_line = false;
	cub->elem.e_counter = 0;
}

// Remplace les '\n' de fin line par '\0'
// Puis dup dans new_line et free la line.
char	*supp_newline(t_cub *cub, char *line)
{
	int		i;
	char	*new_line;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\n')
			line[i] = '\0';
	}
	new_line = ft_strdup(line);
	if (!new_line)
		exit_door(cub, PSG_ALLOC_ERR, NULL);
	free (line);
	return (new_line);
}
