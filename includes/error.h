/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 15:51:25 by pab               #+#    #+#             */
/*   Updated: 2025/10/15 20:25:37 by pbret            ###   ########.fr       */
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
	OK, // 0 Cub3D executed successfully✅
	PSG_FILENAME_ERR, // 1 Invalid file name✅
	PSG_OPEN_FILE_ERR, // 2 Unable to open .cub file✅
	PSG_READ_FILE_ERR, // 3 Error reading the .cub file❌
	PSG_MISS_PARAM_ERR, // 4 Missing parameters❌
	PSG_NO_KEY_ERR, // 5 Unknown or missing element key in line✅
	PSG_ALLOC_ERR, // 6 Memory allocation failed❌
	PSG_LINE_FT_ERR, // 7 Invalid line format✅
	PSG_DUP_PATH_ERR, // 8 Duplicate texture path definition✅
	PSG_DUP_COLOR_ERR, // 9 Duplicate color definition✅
	PSG_PATH_ERR, // 10 Unable to open texture file✅
	PSG_READ_PATH_ERR, // 11 Error reading texture file✅
	PSG_RGB_FT_ERR, // 12 Invalid RGB format❌ -> si derniere valeur supp ->> pas d'erreur
	PSG_EMPTY_MAP_ERR, // 14 Map is empty❌ -> mauvais message d'erreur du a la non distinction d'une erreur d'alloc et la fin du file
	PSG_INV_CHAR_MAP_ERR, // 15 Invalid character found in map✅
	PSG_DUP_PLAYER_ERR, // 16 Multiple player start positions found❌ -> probleme sur la gestion des players (ne controle pas si il ya au moins 1 et "Invalid read of size 1" quand une player est en dernier char d'une ligne)
	PSG_EMPTY_LINE_ERR, // 17 Empty line inside map✅
	PSG_OPEN_MAP_ERR, // 18 Map is not enclosed✅
	PSG_NO_PLAYER_ERR, // 19 No player
	MLX_TXTR_ERR,
	MLX_IMG_ERR,
	MLX_PTR_ERR,
	MLX_WDW_ERR,
	MLX_OTHER_ERR,


	UNKNOWN_ERR, // tjs laisser E_UNKOWN a lafin
}				t_error;
// ✅ ❌

#endif