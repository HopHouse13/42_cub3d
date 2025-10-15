/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_err_msgs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:56:31 by pbret             #+#    #+#             */
/*   Updated: 2025/10/15 15:24:43 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Initialisation du tableau "err_msg".
// Tableau qui contient tous les messages d'erreurs du programme.
void	init_err_msgs(t_cub *cub)
{
	cub->err_msg[OK] = "Cub3D executed successfully";
	cub->err_msg[PSG_FILENAME_ERR] = "Invalid file name";
	cub->err_msg[PSG_OPEN_FILE_ERR] = "Unable to open the .cub file";
	cub->err_msg[PSG_READ_FILE_ERR] = "unable to read the .cub file";
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
	cub->err_msg[MLX_TXTR_ERR] = "Error initializing the textures";
	cub->err_msg[MLX_IMG_ERR] = "Error initializing the images";
	cub->err_msg[MLX_PTR_ERR] = "MLX initialization failed";
	cub->err_msg[MLX_WDW_ERR] = "Window creation failed";
	cub->err_msg[MLX_OTHER_ERR] = "PLACEHOLDER"; // pour le debug
	cub->err_msg[UNKNOWN_ERR] = "Unknown error occurred";
}
