/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ray_debug.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:30:37 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/15 20:45:24 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Il faudrait utiliser fprintf pour print_ray_info sinon c'est illisible
	mais fonction interdite*/
void	print_ray_info(t_ray *ray, int x, FILE *fp)
{
	return ;
	(void) fp;
	if (!PRINT_DEBUG)
		return ;
	printf("		Ray[%d]->map.x =			%.2f		map.y =		\
		%.2f\n", x, ray->map.x, ray->map.y);
	printf("		Ray[%d]->ray_dir.x =		%.4f		ray_dir.y =	\
		%.4f\n", x, ray->ray_dir.x, ray->ray_dir.y);
	printf("		Ray[%d]->delta_dist.x =	%.4f		delta_dist.y =	\
	%.4f\n", x, ray->delta_dist.x, ray->delta_dist.y);
	printf("		Ray[%d]->side_dist.x =	%.4f		side_dist.y =	\
	%.4f\n", x, ray->side_dist.x, ray->side_dist.y);
	printf("		Ray[%d]->step.x =		%.2f		step.y =		\
	%.2f		hit = %d, side = %d, perp_wall_dist = %.4f\n",
		x, ray->step.x, ray->step.y, ray->hit, ray->side, ray->perp_wall_dist);
	printf("		Ray[%d]->line_height =	%d\n", x, ray->line_height);
	printf("		Ray[%d]->draw_start =	%d			draw_end =		\
	%d\n", x, ray->draw_start, ray->draw_end);
}

static void	print_updated_pos2(t_cub *cub, t_player *player)
{
	printf("player->old_time=	%.2f		player->time=		%.2f\n",
		player->old_time, player->time);
	printf("player->frame_time=	%.2f		FPS=			%.2f\n",
		player->frame_time, 1.0 / player->frame_time);
	printf ("player->move_speed=	%.4f		player->rot_speed=	%.4f\n",
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
