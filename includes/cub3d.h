/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:28:01 by pbret             #+#    #+#             */
/*   Updated: 2025/09/11 13:41:36 by pbret            ###   ########.fr       */
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

typedef struct	s_elements
{
	char*	path[4]; // 0 NO, 1 EA, 2 SO, 3 WE
	int		F_value[3]; // init a -1 car 0 valeur accepte
	int		C_value[3];
}			t_elements;


// parsing
void	parsing(char *argv);
void	check_filename(char *argv);
void	check_elem(char *argv);


//main
int	main(int argc, char** argv);


#endif