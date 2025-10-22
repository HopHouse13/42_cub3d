/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:04:22 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/23 01:02:05 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# include "cub3d_bonus.h"

/* ========================================================================== */
/*                               GAME_OPTIONS                                 */
/* ========================================================================== */

# define MAP_MODE 1		// 1 for VIEWPORT 2 for SCALED
# define COLLISION 1
# define PRINT_DEBUG 0
# define BONUS 1
# define FOG 1

/* ========================================================================== */
/*                                  SETTINGS                                  */
/* ========================================================================== */

# define WNDW_W 1920
# define WNDW_H 1080
# define TILE_SIZE 64
# define PLAYER_SIZE 8
# define MNMAP_MARGIN 10
# define MNMAP_TILE_SIZE 16
# define MNMAP_COLS 32
# define MNMAP_ROWS 16
# define MAP_VIEWPORT 1
# define MAP_SCALED 2

/* ========================================================================== */
/*                                GAME_VALUES                                 */
/* ========================================================================== */

# define MOVE_SPEED 0.075
# define ROT_SPEED 0.035
# define MOVE_SPPED_MULT 5.0
# define ROT_SPEED_MULT 3.0
# define FOG_DISTANCE 8
# define FOG_COLOR RGG_BLCK
# define DOOR_ANIM_MS 60
# define DOOR_ANIM_STEP 8
# define DOOR_INTERACT 1.2
# define MAX_SPRITES 100
# define SP_FRAMES 10

/* ========================================================================== */
/*                                RGB_VALUES                                  */
/* ========================================================================== */

# define RGB_WHT 0xFFFFFF
# define DARK_GREY 0x222222
# define RGG_BLCK 0x000000
# define RGB_RED 0xdb4437
# define RGB_BLUE 0x4285f4
# define RGB_YLW 0xf4b400
# define RGB_GRN 0x0f9d58
# define RGB_ORG 0xEC973D
# define DARK_BLUE 0x000067
# define RGB_FLOOR 0xC9C9C9
# define RGB_RAY_YLW 0xFFFF00
# define RGB_LIGHT_GREY 0xC9C9C9
# define LIGHT_GRN 0x98E48B
# define LIGHT_BLUE 0xAEEEEE
# define RGB_BEIGE 0xD2B48C

#endif