/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:11:46 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/13 21:49:15 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"



int	key_press_hook(int keysym, t_cub *cub)
{
	if (keysym == XK_Escape)
		mlx_loop_end(cub->mlx_pointer);
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
	if (cub->player.kbrd.key_w || cub->player.kbrd.key_s || cub->player.kbrd.key_d ||
			cub->player.kbrd.key_a || cub->player.kbrd.key_left || cub->player.kbrd.key_right)
		cub->render_bool = true;
	return (0);
}

int	key_release_hook(int keysym, t_cub *cub)
{

	if (keysym == XK_m)
		cub->player.kbrd.key_m = !cub->player.kbrd.key_m;
	if (keysym == XK_c)
		cub->player.display_cursor = !cub->player.display_cursor;
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