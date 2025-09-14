/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:39:16 by pab               #+#    #+#             */
/*   Updated: 2025/09/14 20:39:48 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_elem(t_elem *elem)
{
		int	i;

	i = -1;
	while(++i < 3)
		printf("elem->f_value[%d] = %d\n", i, elem->f_value[i]);
	i = -1;
	while(++i < 3)
		printf("elem->c_value[%d] = %d\n", i, elem->c_value[i]);
	i = -1;
	while (++i < 4)
		printf("elem->path[%d] = %s\n", i, elem->path[i]);
	printf("elem->start_line = %d\n", elem->start_line);
	printf("elem->e_counter = %d\n", elem->e_counter);
}

void	print_data(t_data *data)
{
	printf("----- DATA -----\n\n");
	print_elem(&data->elem);
	//print_map;
	printf("\n----------------\n\n");

}