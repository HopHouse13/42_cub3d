/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:28:01 by pbret             #+#    #+#             */
/*   Updated: 2025/09/25 20:58:58 by pab              ###   ########.fr       */
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
	OK,
	E_FILENAME, // invalide name file
	E_NO_KEY, // pas trouve de cle d'elem sur la ligne
	E_ALLOC, // probleme lors d'un malloc
	E_LINE_FT, // invalid format de la ligne (garbage char)
	E_DUP_PATH, // doublon de cle de path
	E_DUP_COLOR, // doublon de cle de couleur
	E_PATH, // impossibilite d' ouvrire le path
	E_READ_PATH, // error lors de la lecture du fichier texture (repertoire)	
	E_RGB_FT, // format du RGB invalide
	E_VALUE_COLOR, // error value color
	E_UNKNOWN,
}				t_error;

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
	t_vec		pos;
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
	char		*err_msg[E_UNKNOWN + 1];
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