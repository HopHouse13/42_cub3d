/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:33:57 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/22 19:17:17 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Function that manages the parsing process.
void	parsing(t_cub *cub, char *mapfile)
{
	init_parsing_data(cub);
	print_elem(&(cub->elem));
	check_filename(cub, mapfile);
	check_elem(cub, mapfile);
	check_map(cub, mapfile);
}
