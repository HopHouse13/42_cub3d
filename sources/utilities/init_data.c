/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:56:31 by pbret             #+#    #+#             */
/*   Updated: 2025/09/25 19:07:08 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_elem(t_elem *elem)
{
	int	i;

	i = 0;
	while(i < 3)
	{
		elem->f_value[i] = -1;
		elem->c_value[i] = -1;
		i++;
	}
	i = 0;
	while (i < 4)
		elem->path[i++] = NULL;
	elem->start_line = false;
	elem->e_counter = 0;
}

void	init_err_msgs(char *err_msg)
{
	err_msg[OK] = "Cub3D s'est correctement exectue";
	
}


void	init_data(t_data *data)
{
	data->fd_file = -1;
	data->err_id = OK;
	init_err_msgs(data->err_msg);
	// struct_map
	data->map.tab_map = NULL;
	data->map.nb_line = 0;
	// struct_play
	data->player.ori = '\0';
	data->player.pos.x = 0.0;
	data->player.pos.y = 0.0;
	// struct elem
	init_elem(&data->elem);
}


