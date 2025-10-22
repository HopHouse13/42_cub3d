/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 23:53:06 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/23 01:38:08 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_BONUS_H
# define ERROR_BONUS_H

# include "cub3d_bonus.h"

/* ========================================================================== */
/*                             ERROR MESSAGES                                 */
/* ========================================================================== */

# define OK						"Cub3D executed successfully"
# define PSG_FILENAME_ERR		"Invalid file name"
# define PSG_OPEN_FILE_ERR		"Unable to open the .cub file"
# define PSG_READ_FILE_ERR		"Unable to read the .cub file"
# define PSG_MISS_PARAM_ERR		"Missing parameters"
# define PSG_NO_KEY_ERR			"Missing map elements"
# define PSG_LINE_FT_ERR		"Invalid line format"
# define PSG_DUP_PATH_ERR		"Duplicate texture path definition"
# define PSG_DUP_COLOR_ERR		"Duplicate color definition"
# define PSG_PATH_ERR			"Unable to open texture file"
# define PSG_READ_PATH_ERR		"Unable to read texture file"
# define PSG_OVERFLOW_ERR 		"Integer value exceeds the allowed range"
# define PSG_RGB_FT_ERR			"Invalid RGB format"
# define PSG_EMPTY_MAP_ERR		"Map is empty"
# define PSG_INV_CHAR_MAP_ERR	"Invalid character found in map"
# define PSG_DUP_PLAYER_ERR		"Multiple player start positions found"
# define PSG_EMPTY_LINE_ERR		"Empty line inside map"
# define PSG_OPEN_MAP_ERR		"Map is not enclosed"
# define PSG_NO_PLAYER_ERR		"No player on the map"
# define PSG_DOOR_ERR			"Invalid door on the map"
# define PSG_SP_MAX_ERR			"Too many sprites"
# define MLX_TXTR_ERR			"Unable to initialize the textures"
# define MLX_IMG_ERR			"Unable to initialize the images"
# define MLX_PTR_ERR			"MLX initialization failed"
# define MLX_WDW_ERR			"Window creation failed"
# define ALLOC_ERR				"Memory allocation failed"
# define MLX_OTHER_ERR			"PLACEHOLDER"
# define UNKNOWN_ERR			"Unknown error occurred"

#endif