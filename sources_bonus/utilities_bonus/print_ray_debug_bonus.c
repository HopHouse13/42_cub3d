/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ray_debug_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:30:37 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/23 00:59:26 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	print_sp_txtr_struct(t_txtr *sp_txtr)
{
	int	i;

	if (!PRINT_DEBUG)
		return ;
	printf("/* ---------------------------    print_sp_txtr_struct\
    ------------------------*/\n");
	i = 0;
	while (i < 10)
	{
		printf("	sp_txtr[%d].mlx_img = %p, .addr = %p, .bpp = %d, .line_end = \
%d, .endian = %d, .width = %d, .height = %d\n",
			i, sp_txtr[i].mlx_img, (void *)sp_txtr[i].addr, sp_txtr[i].bpp,
			sp_txtr[i].line_len, sp_txtr[i].endian, sp_txtr[i].width,
			sp_txtr[i].height);
		i++;
	}
	printf("/* -----------------------------------------------------\
-------------------------*/\n\n");
}

void	print_txtr_struct(t_txtr *txtr)
{
	int	i;

	if (!PRINT_DEBUG)
		return ;
	printf("/* ----------------------------    print_txtr_struct\
    -------------------------*/\n");
	i = 0;
	while (i < 5)
	{
		printf("	txtr[%d].mlx_img = %p, .addr = %p, .bpp = %d, .line_end = \
%d, .endian = %d, .width = %d, .height = %d\n",
			i, txtr[i].mlx_img, (void *)txtr[i].addr, txtr[i].bpp, txtr[i].\
line_len, txtr[i].endian, txtr[i].width, txtr[i].height);
		i++;
	}
	printf("/* -----------------------------------------------------\
-------------------------*/\n\n");
}

/* Il faudrait utiliser fprintf pour print_ray_info sinon c'est illisible
	mais fonction interdite*/
void	print_ray_info(t_ray *ray, int x)
{
	return ;
	if (!PRINT_DEBUG)
		return ;
	printf("	Ray[%d]->map.x =		%d		map.y =			%d\n", \
x, ray->map.x, ray->map.y);
	printf("	Ray[%d]->ray_dir.x =		%.4f		ray_dir.y =	\
	%.4f\n", x, ray->ray_dir.x, ray->ray_dir.y);
	printf("	Ray[%d]->delta_dist.x =	%.4f		delta_dist.y =	\
	%.4f\n", x, ray->delta_dist.x, ray->delta_dist.y);
	printf("	Ray[%d]->side_dist.x =	%.4f		side_dist.y =	\
	%.4f\n", x, ray->side_dist.x, ray->side_dist.y);
	printf("	Ray[%d]->step.x =		%d		step.y =		%d\n",
		x, ray->step.x, ray->step.y);
	printf("	Ray[%d]->hit =		%d		side =			%d\n",
		x, ray->hit, ray->side);
	printf("	Ray[%d]->perp_wall_dist =	%g		line_height =		%d\n",
		x, ray->perp_wall_dist, ray->line_height);
	printf("	Ray[%d]->draw_start =		%d		draw_end =		%d\n",
		x, ray->draw_start, ray->draw_end);
	printf("	Ray[%d]->wall_x =		%.4f\n\n", x, ray->wall_x);
}

static void	print_updated_pos2(t_cub *cub, t_player *player)
{
	printf("player->old_time(ms)=	%f	player->time(ms)=	%f\n",
		player->old_time, player->time);
	printf("player->frame_time(ms)=	%f	FPS=			%f\n",
		player->frame_time, 1.0 / player->frame_time);
	printf("player->move_speed=	%.4f		player->rot_speed=	%.4f\n",
		player->move_speed, player->rot_speed);
	printf ("player->display_cursor=	%d		player->cursor_hidden=	%d\n",
		player->display_cursor, player->cursor_hidden);
	printf("player->moves=		%d\n", player->moves);
	printf("/* -----------------------------------------------------------------\
-------------*/\n\n");
	if (cub->game_init)
		cub->game_init = false;
	cub->print_debug_cub = true;
	player->moves++;
}

void	print_updated_pos(t_cub *cub, t_player *player, char *key)
{
	if (!PRINT_DEBUG)
		return ;
	if (cub->game_init)
		printf("/* ----------------------------   print_game_init_pos   \
-------------------------*/\n");
	else
	{
		printf("/* ----------------------------    print_updated_pos    \
-------------------------*/\n");
		printf("	`%s` key pressed\n", key);
	}
	printf ("player->pos.x=		%.4f		player->pos.y=		%.4f\n",
		player->pos.x, player->pos.y);
	printf ("player->plane.x=	%.4f		player->plane.y=	%.4f\n",
		player->plane.x, player->plane.y);
	printf ("player->dir.x=		%.4f		player->dir.y=		%.4f\n",
		player->dir.x, player->dir.y);
	print_updated_pos2(cub, player);
}
