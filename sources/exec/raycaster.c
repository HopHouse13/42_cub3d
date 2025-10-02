/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:11:46 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/02 19:48:38 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"



int	key_press_hook(int keysym, t_player_data *player)
{
	if (keysym == XK_Escape)
		close_window(player->mlx_data_pointer);
	if (keysym == XK_w) // keycode ==
		player->kbrd.key_w = true;
	if (keysym == XK_s)
		player->kbrd.key_s = true;
	if (keysym == XK_a)
		player->kbrd.key_a = true;
	if (keysym == XK_d)
		player->kbrd.key_d = true;
	if (keysym == XK_Left)
		player->kbrd.key_left = true;
	if (keysym == XK_Right)
		player->kbrd.key_right = true;
	return (0);
}

int	key_release_hook(int keysym, t_player_data *player)
{

	if (keysym == XK_m)
	{
		if (player->kbrd.key_m == false)
		{
			player->kbrd.key_m = true;
			printf("player->kbrd.key_m = %d \n", player->kbrd.key_m);
		}
		else
		{
			player->kbrd.key_m = false;
			printf("player->kbrd.key_m = %d \n", player->kbrd.key_m);
		}
	}
	if (keysym == XK_w)
		player->kbrd.key_w = false;
	if (keysym == XK_s)
		player->kbrd.key_s = false;
	if (keysym == XK_a)
		player->kbrd.key_a = false;
	if (keysym == XK_d)
		player->kbrd.key_d = false;
	if (keysym == XK_Left)
		player->kbrd.key_left = false;
	if (keysym == XK_Right)
		player->kbrd.key_right = false;
	return (0);
}

int	exec_launch(void)
{
	t_mlx_data		data;
	t_player_data	player;

	init_data_ray(&data);
	if (!init_player(&player, &data))
		return (1);
	print_map_ray(&(data.map));
	if (!render(&data, &player))
		return (1);
	return (0);
}