/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 15:51:25 by pab               #+#    #+#             */
/*   Updated: 2025/10/11 19:31:37 by tjacquel         ###   ########.fr       */
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
	E_FILENAME, // 1 Invalid file name✅
	E_OPEN_FILE, // 2 Unable to open .cub file✅
	E_READ_FILE, // 3 Error reading the .cub file❌
	E_MISS_PARAM, // 4 Missing parameters❌
	E_NO_KEY, // 5 Unknown or missing element key in line✅
	E_ALLOC, // 6 Memory allocation failed❌
	E_LINE_FT, // 7 Invalid line format✅
	E_DUP_PATH, // 8 Duplicate texture path definition✅
	E_DUP_COLOR, // 9 Duplicate color definition✅
	E_PATH, // 10 Unable to open texture file✅
	E_READ_PATH, // 11 Error reading texture file✅
	E_RGB_FT, // 12 Invalid RGB format❌ -> si derniere valeur supp ->> pas d'erreur
	E_VALUE_COLOR, // 13 Invalid color value✅
	E_EMPTY_MAP, // 14 Map is empty❌ -> mauvais message d'erreur du a la non distinction d'une erreur d'alloc et la fin du file
	E_INV_CHAR_MAP, // 15 Invalid character found in map✅
	E_DUP_PLAYER, // 16 Multiple player start positions found❌ -> probleme sur la gestion des players (ne controle pas si il ya au moins 1 et "Invalid read of size 1" quand une player est en dernier char d'une ligne)
	E_EMPTY_LINE, // 17 Empty line inside map✅
	E_OPEN_MAP, // 18 Map is not enclosed✅
	E_NO_PLAYER, // 19 No player
	MLX_TXTR_ERR,
	MLX_IMG_ERR,
	MLX_PTR_ERR,
	MLX_WDW_ERR,
	MLX_OTHER_ERR,


	E_UNKNOWN,// Unknown error occurred // tjs laisser E_UNKOWN a lafin
}				t_error;
// ✅ ❌

#endif