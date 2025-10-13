/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_mvmt_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:21:34 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/13 21:58:20 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_mouse(int x, int y, t_cub *cub)
{
	int		dx;
	int		center_x;

	(void) y;
	center_x = WNDW_W / 2;
	if (!cub->player.display_cursor)
	{
		if (x == center_x)
			return (0);
		dx = x - center_x;
		if (dx > 0)
			turn_around(cub, &(cub->player), 'R');
		else if (dx < 0)
			turn_around(cub, &(cub->player), 'L');
		mlx_mouse_move(cub->mlx_pointer, cub->mlx_window, center_x, WNDW_H / 2);
	}
	return (0);
}
