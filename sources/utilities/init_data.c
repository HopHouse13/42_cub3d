/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:56:31 by pbret             #+#    #+#             */
/*   Updated: 2025/09/12 14:32:53 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_elem(t_elem *elem)
{
		int	i;

	i = 0;
	while(i < 3)
	{
		printf("elem->f_value[%d] = %d\n", i, elem->f_value[i]);
		printf("elem->c_value[%d] = %d\n", i, elem->c_value[i]);
		i++;
	}
	i = -1;
	while (++i < 4)
	{
		printf("elem->path[%d] = %s\n", i, elem->path[i]);
		//i++;
	}
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

void	init_elem(t_elem *elem)
{
	int	i;

	i = 0;
	while(i < 3)
	{
		elem->f_value[i] = -1;
		elem->c_value[i] = -1;
		i++;
	}
	i = 0;
	while (i < 4)
		elem->path[i++] = NULL;
	elem->start_line = false;
	elem->e_counter = 0;
}

void	init_data(t_data *data)
{
	init_elem(&data->elem);
}


