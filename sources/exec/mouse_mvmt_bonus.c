/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_mvmt_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:21:34 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/20 16:54:50 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_mouse(int x, int y, t_cub *cub)
{
	int		dx;
	int		center_x;

	(void) y;
	center_x = WNDW_W / 2;
	if (!cub->player.display_cursor && cub->player.cursor_hidden)
	{
		if (x == center_x)
			return (0);
		dx = x - center_x;
		if (dx > 0)
			turn_right(cub, &(cub->player), true);
		else if (dx < 0)
			turn_left(cub, &(cub->player), true);
		mlx_mouse_move(cub->mlx_pointer, cub->mlx_window, center_x, WNDW_H / 2);
	}
	return (0);
}

int	handle_focus_out(t_cub *cub)
{
	if (!cub->player.display_cursor && cub->player.cursor_hidden)
	{
		mlx_mouse_show(cub->mlx_pointer, cub->mlx_window);
		cub->player.cursor_hidden = false;
	}
	return (0);
}

int	handle_focus_in(t_cub *cub)
{
	if (!cub->player.display_cursor && !cub->player.cursor_hidden)
	{
		mlx_mouse_hide(cub->mlx_pointer, cub->mlx_window);
		cub->player.cursor_hidden = true;
	}
	return (0);
}

void	toggle_cursor_bonus(t_cub *cub)
{
	cub->player.display_cursor = !cub->player.display_cursor;
	if (!cub->player.display_cursor)
	{
		mlx_mouse_hide(cub->mlx_pointer, cub->mlx_window);
		cub->player.cursor_hidden = true;
	}
	else
	{
		mlx_mouse_show(cub->mlx_pointer, cub->mlx_window);
		cub->player.cursor_hidden = false;
	}
}

void	mouse_mlx_hook_bonus(t_cub *cub)
{
	if (!BONUS)
		return ;
	mlx_hook(cub->mlx_window, MotionNotify, PointerMotionMask,
		&handle_mouse, cub);
	mlx_hook(cub->mlx_window, FocusIn, FocusChangeMask,
		&handle_focus_in, cub);
	mlx_hook(cub->mlx_window, FocusOut, FocusChangeMask,
		&handle_focus_out, cub);
}
