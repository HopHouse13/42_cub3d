/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:11:46 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/08 18:50:11 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"



int	key_press_hook(int keysym, t_cub *cub)
{
	if (keysym == XK_Escape)
		close_window(cub);
	if (keysym == XK_w) // keycode ==
		cub->player.kbrd.key_w = true;
	if (keysym == XK_s)
		cub->player.kbrd.key_s = true;
	if (keysym == XK_a)
		cub->player.kbrd.key_a = true;
	if (keysym == XK_d)
		cub->player.kbrd.key_d = true;
	if (keysym == XK_Left)
		cub->player.kbrd.key_left = true;
	if (keysym == XK_Right)
		cub->player.kbrd.key_right = true;
	return (0);
}

int	key_release_hook(int keysym, t_cub *cub)
{

	if (keysym == XK_m)
	{
		if (cub->player.kbrd.key_m == false)
		{
			cub->player.kbrd.key_m = true;
			printf("cub->player.kbrd.key_m = %d \n", cub->player.kbrd.key_m);
		}
		else
		{
			cub->player.kbrd.key_m = false;
			printf("cub->player.kbrd.key_m = %d \n", cub->player.kbrd.key_m);
		}
	}
	if (keysym == XK_w)
		cub->player.kbrd.key_w = false;
	if (keysym == XK_s)
		cub->player.kbrd.key_s = false;
	if (keysym == XK_a)
		cub->player.kbrd.key_a = false;
	if (keysym == XK_d)
		cub->player.kbrd.key_d = false;
	if (keysym == XK_Left)
		cub->player.kbrd.key_left = false;
	if (keysym == XK_Right)
		cub->player.kbrd.key_right = false;
	return (0);
}

int	exec_launch(t_cub *cub)
{
	init_exec_data(cub);
	if (!init_player(cub, &(cub->player)))
		return (1);
	print_map_ray(&(cub->map));
	print_elem(&(cub->elem));
	if (!render(cub))
		return (1);
	return (0);
}