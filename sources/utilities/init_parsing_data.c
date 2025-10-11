/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing_data.c                                        :+:      :+:    :+:   */
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
	cub->err_msg[PSG_FILENAME_ERR] = "Invalid file name";
	cub->err_msg[PSG_OPEN_FILE_ERR] = "Unable to open .cub file";
	cub->err_msg[PSG_READ_FILE_ERR] = "Error reading the .cub file";
	cub->err_msg[PSG_MISS_PARAM_ERR] = "Missing parameters";
	cub->err_msg[PSG_NO_KEY_ERR] = "Unknown or missing element key in line";
	cub->err_msg[PSG_ALLOC_ERR] = "Memory allocation failed";
	cub->err_msg[PSG_LINE_FT_ERR] = "Invalid line format";
	cub->err_msg[PSG_DUP_PATH_ERR] = "Duplicate texture path definition";
	cub->err_msg[PSG_DUP_COLOR_ERR] = "Duplicate color definition";
	cub->err_msg[PSG_PATH_ERR] = "Unable to open texture file";
	cub->err_msg[PSG_READ_PATH_ERR] = "Error reading texture file";
	cub->err_msg[PSG_RGB_FT_ERR] = "Invalid RGB format";
	cub->err_msg[PSG_VALUE_COLOR_ERR] = "Invalid color value";
	cub->err_msg[PSG_EMPTY_MAP_ERR] = "Map is empty";
	cub->err_msg[PSG_INV_CHAR_MAP_ERR] = "Invalid character found in map";
	cub->err_msg[PSG_DUP_PLAYER_ERR] = "Multiple player start positions found";
	cub->err_msg[PSG_EMPTY_LINE_ERR] = "Empty line inside map";
	cub->err_msg[PSG_OPEN_MAP_ERR] = "Map is not enclosed";
	cub->err_msg[PSG_NO_PLAYER_ERR] = "No player on the map";
	cub->err_msg[UNKNOWN_ERR] = "Unknown error occurred";
	//cub->err_msg[] = "";
	cub->err_msg[MLX_TXTR_ERR] = "Error initializing the textures";
	cub->err_msg[MLX_IMG_ERR] = "PLACEHOLDER";
	cub->err_msg[MLX_PTR_ERR] = "MLX initialization failed";
	cub->err_msg[MLX_WDW_ERR] = "Window creation failed";
	cub->err_msg[MLX_OTHER_ERR] = "PLACEHOLDER";


}

void	init_parsing_data(t_cub *cub)
{
	init_err_msgs(cub);
	cub->fd_file = -1;
	// struct_map
	cub->map.grid = NULL;
	cub->map.rows = 0;
	cub->map.max_col = 0;
	// struct_play
	cub->player.pos.x = 0.0;
	cub->player.pos.y = 0.0;
	// struct elem
	init_elem(&cub->elem);
}
