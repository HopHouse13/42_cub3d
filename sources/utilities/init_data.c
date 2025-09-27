/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:56:31 by pbret             #+#    #+#             */
/*   Updated: 2025/09/27 16:06:37 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_elem(t_elem *elem)
{
	int	i;

	i = 0;
	while (i < 3)
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

void	init_err_msgs(t_data *data)
{
	data->err_msg[OK] = "Cub3D executed successfully";
	data->err_msg[E_FILENAME] = "Invalid file name";
	data->err_msg[E_OPEN_FILE] = "Unable to open .cub file";
	data->err_msg[E_READ_FILE] = "Error reading the .cub file";
	data->err_msg[E_MISS_PARAM] = "Missing parameters";
	data->err_msg[E_NO_KEY] = "Unknown or missing element key in line";
	data->err_msg[E_ALLOC] = "Memory allocation failed";
	data->err_msg[E_LINE_FT] = "Invalid line format";
	data->err_msg[E_DUP_PATH] = "Duplicate texture path definition";
	data->err_msg[E_DUP_COLOR] = "Duplicate color definition";
	data->err_msg[E_PATH] = "Unable to open texture file";
	data->err_msg[E_READ_PATH] = "Error reading texture file";
	data->err_msg[E_RGB_FT] = "Invalid RGB format";
	data->err_msg[E_VALUE_COLOR] = "Invalid color value";
	data->err_msg[E_EMPTY_MAP] = "Map is empty";
	data->err_msg[E_INV_CHAR_MAP] = "Invalid character found in map";
	data->err_msg[E_DUP_PLAYER] = "Multiple player start positions found";
	data->err_msg[E_EMPTY_LINE] = "Empty line inside map";
	data->err_msg[E_OPEN_MAP] = "Map is not enclosed";
	data->err_msg[E_UNKNOWN] = "Unknown error occurred";
	//data->err_msg[] = "";
}

void	init_data(t_data *data)
{
	data->fd_file = -1;
	init_err_msgs(data);
	// struct_map
	data->map.tab_map = NULL;
	data->map.nb_line = 0;
	// struct_play
	data->player.ori = '\0';
	data->player.position.x = 0.0;
	data->player.position.y = 0.0;
	// struct elem
	init_elem(&data->elem);
}
