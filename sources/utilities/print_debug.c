/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:39:16 by pab               #+#    #+#             */
/*   Updated: 2025/10/22 21:28:56 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_map(char **map)
{
	int	i;

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
	while (++i < 3)
		printf("elem->f_values[%d] = %d\n", i, elem->f_values[i]);
	printf("elem->f_color = %d\n", elem->f_color);
	i = -1;
	while (++i < 3)
		printf("elem->c_values[%d] = %d\n", i, elem->c_values[i]);
	printf("elem->c_color = %d\n", elem->c_color);
	i = -1;
	while (++i < 15)
		printf("elem->path[%d] = %s\n", i, elem->path[i]);
	printf("elem->facing = %c\n", elem->facing);
	printf("elem->start_line = %d\n", elem->start_line);
	printf("elem->e_counter = %d\n", elem->e_counter);
	printf("elem->doors_nb = %d\n", elem->doors_nb);
	printf("elem->sprite_nb = %d\n", elem->sprite_nb);
}

void	print_cub_data(t_cub *cub)
{
	printf("----- DATA -----\n\n");
	print_elem(&cub->elem);
	print_map(cub->map.grid);
	printf("\n----------------\n\n");
}

void	print_sprites(t_cub *cub)
{
	int	i;

	if (cub->elem.sprite_nb < 1)
		return ;
	if (!PRINT_DEBUG)
		return ;
	i = 0;
	if (cub->game_init)
		printf("		----------  SPRITES  ----------\n");
	while (i < cub->elem.sprite_nb)
	{
		if (cub->game_init || cub->sprites[i].action)
			printf("		Sprite[%d] coord{%.2f, %.2f} active[%d] frame_count[%d] current_frame[%d] frame_duration[%.2f] elapsed_time[%.2f] loop[%d] action[%d]\n",
				i, cub->sprites[i].pos.x, cub->sprites[i].pos.y,
				 cub->sprites[i].active, cub->sprites[i].frame_count, cub->sprites[i].current_frame, cub->sprites[i].frame_duration, cub->sprites[i].elapsed_time, cub->sprites[i].loop, cub->sprites[i].action);
		cub->sprites[i].action = false;
		i++;
	}
	if (cub->game_init)
		printf("\n");
}