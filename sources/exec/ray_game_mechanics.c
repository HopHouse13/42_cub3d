/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_game_mechanics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 19:10:39 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/06 19:01:11 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_ray_info(t_ray *ray, int x, FILE *fp)
{
		fprintf(fp, "		Ray[%d]->map.x =			%.2f		map.y =				%.2f\n", x, ray->map.x, ray->map.y);
		fprintf(fp, "		Ray[%d]->ray_dir.x =		%.4f		ray_dir.y =			%.4f\n", x, ray->ray_dir.x, ray->ray_dir.y);
		fprintf(fp, "		Ray[%d]->delta_dist.x =		%.4f		delta_dist.y =		%.4f\n", x, ray->delta_dist.x, ray->delta_dist.y);
		fprintf(fp, "		Ray[%d]->side_dist.x =		%.4f		side_dist.y =		%.4f\n", x, ray->side_dist.x, ray->side_dist.y);
		fprintf(fp, "		Ray[%d]->step.x =			%.2f		step.y =			%.2f		 hit = %d, side = %d, perp_wall_dist = %.4f\n",
							x, ray->step.x, ray->step.y, ray->hit, ray->side, ray->perp_wall_dist);




}

void	print_updated_pos(t_player *player, t_ray *ray)
{
	printf("/* ----------------------------    print_updated_pos    -------------------------*/\n");
	printf ("player->pos.x = %.4f\n", player->pos.x);
	printf ("player->pos.y = %.4f\n", player->pos.y);
	printf ("player->plane.x = %.4f\n", player->plane.x);
	printf ("player->plane.y = %.4f\n", player->plane.y);
	printf ("player->dir.x = %.4f\n", player->dir.x);
	printf ("player->dir.y = %.4f\n", player->dir.y);
	printf("player->old_time = %.2f		player->time = %.2f		player->frame_time = %.2f	FPS = %.2f\n", player->old_time, player->time, player->frame_time, 1.0 / player->frame_time);
	printf ("player->move_speed = %.4f\n", player->move_speed);
	printf ("player->rot_speed = %.4f\n", player->rot_speed);
	printf("/* ------------------------------------------------------------------------------*/\n\n");

	if (ray->game_init)
		ray->game_init = false;

}

void	handle_move(t_cub *cub, t_player *player, t_ray *ray)
{
	if (player->kbrd.key_w)
	{
		printf ("W pressed \n" );


		if (player->pos.x + player->dir.x * player->move_speed >= 1 && player->pos.x + player->dir.x * player->move_speed < cub->map.cols
			&& cub->map.grid[(int)player->pos.y][(int)(player->pos.x + player->dir.x * player->move_speed)] != '1')
			player->pos.x += player->dir.x * player->move_speed;
		if (player->pos.y + player->dir.y * player->move_speed >= 1 && player->pos.y + player->dir.x * player->move_speed < cub->map.rows
			&& cub->map.grid[(int)(player->pos.y + player->dir.y * player->move_speed)][(int)player->pos.x] != '1')
			player->pos.y += player->dir.y * player->move_speed;
		print_updated_pos(player, ray);
		ray->print_debug = true;

	}

	if (player->kbrd.key_s)
	{
		printf ("S pressed \n" );

		if (player->pos.x - player->dir.x * player->move_speed >= 1 && player->pos.x - player->dir.x * player->move_speed < cub->map.cols
				&& cub->map.grid[(int)player->pos.y][(int)(player->pos.x - player->dir.x * player->move_speed)] != '1')
			player->pos.x -= player->dir.x * player->move_speed;
		if (player->pos.y - player->dir.y * player->move_speed >= 1 && player->pos.y - player->dir.x * player->move_speed < cub->map.rows
				&& cub->map.grid[(int)(player->pos.y - player->dir.y * player->move_speed)][(int)player->pos.x] != '1')
			player->pos.y -= player->dir.y * player->move_speed;
		print_updated_pos(player, ray);
		ray->print_debug = true;


	}
	if (player->kbrd.key_d)
	{
		printf ("A pressed \n" );

		// Move perpendicular to the right: use (dir.y, -dir.x)
		double strafeX = -player->dir.y * player->move_speed;
		double strafeY = player->dir.x * player->move_speed;

		if (player->pos.x + strafeX >= 1 && player->pos.x + strafeX < cub->map.cols
				&& cub->map.grid[(int)player->pos.y][(int)(player->pos.x + strafeX)] != '1')
			player->pos.x += strafeX;
		if (player->pos.y + strafeY >= 1 && player->pos.y + strafeY < cub->map.rows
				&& cub->map.grid[(int)(player->pos.y + strafeY)][(int)player->pos.x] != '1')
			player->pos.y += strafeY;
		print_updated_pos(player, ray);
		ray->print_debug = true;

	}

	if (player->kbrd.key_a)
	{
		// Move perpendicular to the left: use (-dir.y, dir.x)
		printf ("S pressed \n" );

		double strafeX = player->dir.y * player->move_speed;
		double strafeY = -player->dir.x * player->move_speed;

		if (player->pos.x + strafeX >= 1 && player->pos.x + strafeX < cub->map.cols
				&& cub->map.grid[(int)player->pos.y][(int)(player->pos.x + strafeX)] != '1')
			player->pos.x += strafeX;
		if (player->pos.y + strafeY >= 1 && player->pos.y + strafeY < cub->map.rows
				&& cub->map.grid[(int)(player->pos.y + strafeY)][(int)player->pos.x] != '1')
			player->pos.y += strafeY;
		print_updated_pos(player, ray);
		ray->print_debug = true;

	}
	if (player->kbrd.key_left)
	{
		printf ("left arrow pressed \n" );
		//	Matrice de rotation 2D
		double	oldDirX = player->dir.x;
		player->dir.x = player->dir.x * cos(- player->rot_speed) - player->dir.y * sin(- player->rot_speed);
		player->dir.y = oldDirX * sin(- player->rot_speed) + player->dir.y * cos(-player->rot_speed);

		//	Matrice de rotation 2D
		double	oldPlaneX = player->plane.x;
		player->plane.x = player->plane.x * cos( - player->rot_speed) - player->plane.y * sin( - player->rot_speed);
		player->plane.y = oldPlaneX * sin(- player->rot_speed) + player->plane.y * cos(- player->rot_speed);
		print_updated_pos(player, ray);
		ray->print_debug = true;

	}

	if (player->kbrd.key_right)
	{
		printf ("right arrow pressed \n" );
		//	Matrice de rotation 2D
		double	oldDirX = player->dir.x;
		player->dir.x = player->dir.x * cos(player->rot_speed) - player->dir.y * sin(player->rot_speed);
		player->dir.y = oldDirX * sin(player->rot_speed) + player->dir.y * cos(player->rot_speed);

		//	Matrice de rotation 2D
		double	oldPlaneX = player->plane.x;
		player->plane.x = player->plane.x * cos(player->rot_speed) - player->plane.y * sin(player->rot_speed);
		player->plane.y = oldPlaneX * sin(player->rot_speed) + player->plane.y * cos(player->rot_speed);
		print_updated_pos(player, ray);
		ray->print_debug = true;

	}

}
