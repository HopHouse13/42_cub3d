/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:37:49 by pab               #+#    #+#             */
/*   Updated: 2025/09/25 18:57:33 by pab              ###   ########.fr       */
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

	i = 0;
	while (data->elem.path[i] && i < 4) // il n'y a pas de chaine de caracte de fin ('\0') mais nous savons qu'il exatement 4 chaines a liberer
		free(data->elem.path[i++]);
}

void	exit_door(t_data *data, t_error err_id)
{
	if (err_id)
		printf("Error\n");
	printf("%s\n", data->err_msg[err_id]);
	

	
	if (data->fd_file >= 0)
		close(data->fd_file);
	free_elem(data);
	free_map(data);
	exit (2);
}