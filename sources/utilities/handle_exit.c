/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:37:49 by pab               #+#    #+#             */
/*   Updated: 2025/09/16 12:55:24 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_map(t_data *data)
{
	int	i;

	if (!data->map.map)
		return;
	i = 0;
	while (data->map.map[i])
		free(data->map.map[i++]);
	free(data->map.map);
}

static void	free_elem(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4) // il n'y a pas de chaine de caracte de fin ('\0') mais nous savons qu'il exatement 4 chaines a liberer
		free(data->elem.path[i++]);
}

void	exit_door(t_data *data, char *str)
{
	printf("Error\n%s\n", str);
	if (data->fd_file >= 0)
		close(data->fd_file);
	free_elem(data);
	free_map(data);
	exit (2);
}