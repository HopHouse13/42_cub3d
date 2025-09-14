/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:28:01 by pbret             #+#    #+#             */
/*   Updated: 2025/09/14 21:05:20 by pab              ###   ########.fr       */
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

typedef enum	e_key
{
	NO,
	EA,
	SO,
	WE,
	F,
	C,
}				t_key;

typedef struct	s_elements
{
	char*	path[4]; // 0 NO, 1 EA, 2 SO, 3 WE
	int		f_value[3]; // init a -1 car 0 valeur accepte
	int		c_value[3];
	bool	start_line;
	int		e_counter;
}			t_elem;

typedef struct	s_data
{
	t_elem	elem;
}			t_data;

/// PARSING ///
void	parsing(t_data *data, char *argv);
void	check_filename(t_data *data, char *argv);
void	check_param(t_data *data, char *file_map);

/// UTILITIES ///

// handle_exit
void	exit_door(t_data *data, char *str);

// init_data
void	init_data(t_data *data);
void	init_elem(t_elem *elem);

// print_debug
void	print_data(t_data *data);
void	print_elem(t_elem *elem);

#endif