/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:37:49 by pab               #+#    #+#             */
/*   Updated: 2025/10/03 19:06:12 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_map(t_cub *cub)
{
	int	i;

	if (!cub->map.tab_map)
		return;
	i = 0;
	while (cub->map.tab_map[i])
		free(cub->map.tab_map[i++]);
	free(cub->map.tab_map);
}

static void	free_elem(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4) // il n'y a pas de chaine de char de fin ('\0') mais nous savons qu'il exatement 4 chaines a liberer
	{
		if (cub->elem.path[i])
			free(cub->elem.path[i]);
	}
}


static void freee(t_cub *cub)
{
	t_error	err_id;

	if (cub->fd_file >= 0)
		close(cub->fd_file);
	get_next_line(-1, &err_id, true);
	free_elem(cub);
	free_map(cub);
	exit (2);
}

void	exit_door(t_cub *cub, t_error err_id)
{printf("||||| EXIT_DOOR |||||\n");
	if (err_id < OK)
		err_id = E_UNKNOWN;
	if (err_id > OK)
		printf("Error\n");
	printf("%s\n", cub->err_msg[err_id]);
	freee(cub);
}