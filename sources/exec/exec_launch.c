/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:11:46 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/23 01:04:25 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	key_press_hook(int keysym, t_cub *cub)
{
	if (keysym == XK_Escape)
		mlx_loop_end(cub->mlx_pointer);
	if (keysym == XK_w)
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

void	exec_launch(t_cub *cub)
{
	init_exec_data(cub);
	init_player(cub, &(cub->player));
	render(cub);
}
