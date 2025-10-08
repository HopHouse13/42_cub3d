/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:56:31 by pbret             #+#    #+#             */
/*   Updated: 2025/10/03 19:06:12 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_elem(t_elem *elem)
{
	int	i;

	i = 0;
	while (i < 4)
		elem->path[i++] = NULL;
	i = 0;
	while (i < 3)
	{
		elem->f_values[i] = -1;
		elem->c_values[i++] = -1;
	}
	elem->f_color = -1;
	elem->c_color = -1;
	elem->facing = 0;
	elem->start_line = false;
	elem->e_counter = 0;
}

void	init_err_msgs(t_cub *cub)
{
	cub->err_msg[OK] = "Cub3D executed successfully";
	cub->err_msg[E_FILENAME] = "Invalid file name";
	cub->err_msg[E_OPEN_FILE] = "Unable to open .cub file";
	cub->err_msg[E_READ_FILE] = "Error reading the .cub file";
	cub->err_msg[E_MISS_PARAM] = "Missing parameters";
	cub->err_msg[E_NO_KEY] = "Unknown or missing element key in line";
	cub->err_msg[E_ALLOC] = "Memory allocation failed";
	cub->err_msg[E_LINE_FT] = "Invalid line format";
	cub->err_msg[E_DUP_PATH] = "Duplicate texture path definition";
	cub->err_msg[E_DUP_COLOR] = "Duplicate color definition";
	cub->err_msg[E_PATH] = "Unable to open texture file";
	cub->err_msg[E_READ_PATH] = "Error reading texture file";
	cub->err_msg[E_RGB_FT] = "Invalid RGB format";
	cub->err_msg[E_VALUE_COLOR] = "Invalid color value";
	cub->err_msg[E_EMPTY_MAP] = "Map is empty";
	cub->err_msg[E_INV_CHAR_MAP] = "Invalid character found in map";
	cub->err_msg[E_DUP_PLAYER] = "Multiple player start positions found";
	cub->err_msg[E_EMPTY_LINE] = "Empty line inside map";
	cub->err_msg[E_OPEN_MAP] = "Map is not enclosed";
	cub->err_msg[E_NO_PLAYER] = "No player on the map";
	cub->err_msg[E_UNKNOWN] = "Unknown error occurred";
	//cub->err_msg[] = "";
}

void	init_cub_data(t_cub *cub)
{
	cub->fd_file = -1;
	init_err_msgs(cub);
	// struct_map
	cub->map.grid = NULL;
	cub->map.rows = 0;
	cub->map.max_col = 0;
	// struct_play
	cub->player.facing = '\0';
	cub->player.pos.x = 0.0;
	cub->player.pos.y = 0.0;
	// struct elem
	init_elem(&cub->elem);
}
