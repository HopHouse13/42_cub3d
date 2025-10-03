/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:33:57 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/03 19:06:12 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	parsing(t_cub *cub, char *mapfile)
{
	check_filename(cub, mapfile);
	check_elem(cub, mapfile);
	check_map(cub, mapfile);

}