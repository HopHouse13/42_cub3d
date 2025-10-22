/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 15:51:25 by pab               #+#    #+#             */
/*   Updated: 2025/10/22 14:18:40 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

// typedef enum	e_mlx_err
// {
// 	MLX_OK,
// 	MLX_TXTR_ERR,
// 	MLX_IMG_ERR,
// 	MLX_PTR_ERR,
// 	MLX_OTHER_ERR,
// }				t_mlx_err;


typedef enum	e_error
{
	OK,
	PSG_FILENAME_ERR,
	PSG_OPEN_FILE_ERR,
	PSG_READ_FILE_ERR,
	PSG_MISS_PARAM_ERR,
	PSG_NO_KEY_ERR,
	PSG_ALLOC_ERR,
	PSG_LINE_FT_ERR,
	PSG_DUP_PATH_ERR,
	PSG_DUP_COLOR_ERR,
	PSG_PATH_ERR,
	PSG_READ_PATH_ERR,
	PSG_RGB_FT_ERR,
	PSG_EMPTY_MAP_ERR,
	PSG_INV_CHAR_MAP_ERR,
	PSG_DUP_PLAYER_ERR,
	PSG_EMPTY_LINE_ERR,
	PSG_OPEN_MAP_ERR,
	PSG_NO_PLAYER_ERR,
	PSG_DOOR_ERR,
	MLX_TXTR_ERR,
	MLX_IMG_ERR,
	MLX_PTR_ERR,
	MLX_WDW_ERR,
	MLX_OTHER_ERR,

	UNKNOWN_ERR,
}				t_error;

#endif