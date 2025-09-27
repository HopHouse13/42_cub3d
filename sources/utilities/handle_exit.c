/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:37:49 by pab               #+#    #+#             */
/*   Updated: 2025/09/27 16:05:53 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_map(t_data *data)
{
	int	i;

	if (!data->map.tab_map)
		return;
	i = 0;
	while (data->map.tab_map[i])
		free(data->map.tab_map[i++]);
	free(data->map.tab_map);
}

static void	free_elem(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4) // il n'y a pas de chaine de char de fin ('\0') mais nous savons qu'il exatement 4 chaines a liberer
	{
		if (data->elem.path[i])
			free(data->elem.path[i]);
	}
}


static void freee(t_data *data)
{
	t_error	err_id;

	if (data->fd_file >= 0)
		close(data->fd_file);
	get_next_line(-1, &err_id, true);
	free_elem(data);
	free_map(data);
	exit (2);
}

void	exit_door(t_data *data, t_error err_id)
{printf("||||| EXIT_DOOR |||||\n");
	if (err_id < 0)
		err_id = E_UNKNOWN;
	if (err_id > 0)
		printf("Error\n");
	printf("%s\n", data->err_msg[err_id]);
	freee(data);
}