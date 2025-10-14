/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:39:16 by pab               #+#    #+#             */
/*   Updated: 2025/10/14 16:25:21 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_map(char **map)
{
	int i;

	printf("||||| MAP |||||\n");
	i = 0;
	while (map[i])
		printf("%s\n", map[i++]);
	printf("||||| FIN DE MAP |||||\n");
}

void	print_elem(t_elem *elem)
{
		int	i;

	i = -1;
	while(++i < 3)
		printf("elem->f_values[%d] = %d\n", i, elem->f_values[i]);
	printf("elem->f_color = %d\n",elem->f_color);
	i = -1;
	while(++i < 3)
		printf("elem->c_values[%d] = %d\n", i, elem->c_values[i]);
	printf("elem->c_color = %d\n", elem->c_color);
	i = -1;
	while (++i < 4)
		printf("elem->path[%d] = %s\n", i, elem->path[i]);
	printf("elem->facing = %c\n", elem->facing);
	printf("elem->start_line = %d\n", elem->start_line);
	printf("elem->e_counter = %d\n", elem->e_counter);
}

void	print_cub_data(t_cub *cub)
{
	printf("----- DATA -----\n\n");
	print_elem(&cub->elem);
	print_map(cub->map.grid);
	printf("\n----------------\n\n");

}