/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:28:01 by pbret             #+#    #+#             */
/*   Updated: 2025/09/26 17:17:45 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/get_next_line/get_next_line.h"

# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>

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
	E_UNKNOWN,// 19 Unknown error occurred
}				t_error;
// ✅ ❌
typedef enum	e_key
{
	NO,
	EA,
	SO,
	WE,
	F,
	C,
}				t_key;

typedef struct	s_vec
{
	float		x;
	float		y;
}				t_vec;

typedef struct	s_player
{
	t_vec		position;
	char		ori;
}				t_player;

typedef struct	s_map
{
	char 		**tab_map;
	int			nb_line;
}				t_map;

typedef struct	s_elements
{
	char		*path[4]; // 0 NO, 1 EA, 2 SO, 3 WE
	int			f_value[3]; // init a -1 car 0 valeur accepte
	int			c_value[3];
	bool		start_line;
	int			e_counter;
}				t_elem;

typedef struct	s_data
{
	t_map		map;
	t_elem		elem;
	t_player	player;
	int			fd_file;
	char		*err_msg[E_UNKNOWN];
}			t_data;

/// PARSING ///
void	parsing(t_data *data, char *argv);
void	check_filename(t_data *data, char *argv);
void	check_elem(t_data *data, char *file_map);

void	check_map(t_data *data, char *mapfile);
void	make_copy(t_data *data, char *mapfile);
bool	is_empty(char *line);

/// UTILITIES ///

// handle_exit
void	exit_door(t_data *data, t_error err_id);

// init_data
void	init_data(t_data *data);
void	init_elem(t_elem *elem);

// print_debug
void	print_data(t_data *data);
void	print_elem(t_elem *elem);
void	print_map(char **map);

#endif