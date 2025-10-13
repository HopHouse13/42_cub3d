/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_game_mechanics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 19:10:39 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/13 21:30:30 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_ray_info(t_ray *ray, int x, FILE *fp)
{
		fprintf(fp, "		Ray[%d]->map.x =			%.2f		map.y =				%.2f\n", x, ray->map.x, ray->map.y);
		fprintf(fp, "		Ray[%d]->ray_dir.x =		%.4f		ray_dir.y =			%.4f\n", x, ray->ray_dir.x, ray->ray_dir.y);
		fprintf(fp, "		Ray[%d]->delta_dist.x =	%.4f		delta_dist.y =		%.4f\n", x, ray->delta_dist.x, ray->delta_dist.y);
		fprintf(fp, "		Ray[%d]->side_dist.x =	%.4f		side_dist.y =		%.4f\n", x, ray->side_dist.x, ray->side_dist.y);
		fprintf(fp, "		Ray[%d]->step.x =		%.2f		step.y =			%.2f		hit = %d, side = %d, perp_wall_dist = %.4f\n",
							x, ray->step.x, ray->step.y, ray->hit, ray->side, ray->perp_wall_dist);
		fprintf(fp, "		Ray[%d]->line_height =	%d\n", x, ray->line_height);
		fprintf(fp, "		Ray[%d]->draw_start =	%d			draw_end =			%d\n", x, ray->draw_start, ray->draw_end);






}

void	print_updated_pos(t_cub *cub, t_player *player)
{
	if (cub->game_init)
		printf("/* ----------------------------   print_game_init_pos   -------------------------*/\n");
	else
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
	printf("cub->moves = %d\n", cub->moves);
	printf("/* ------------------------------------------------------------------------------*/\n\n");

	if (cub->game_init)
		cub->game_init = false;
	cub->print_debug_cub = true;


}

void	no_collision_move(t_cub *cub, t_player *player)
{
	if (player->kbrd.key_w)
	{
		printf ("W pressed \n" );
		double new_x = player->pos.x + player->dir.x * player->move_speed;
		double new_y = player->pos.y + player->dir.y * player->move_speed;

		// Check X bounds and row length
		if (new_x >= 0 && new_x < cub->map.max_col)
		{
			int row = (int)player->pos.y;
			if (row >= 0 && row <(int)cub->map.rows && new_x < (int)ft_strlen(cub->map.grid[row]))
				player->pos.x = new_x;
		}

		// Check Y bounds
		if (new_y >= 0 && new_y <=cub->map.rows)
		{
			int col = (int)player->pos.x;
			int new_row = (int)new_y;
			if (new_row >= 0 && new_row <=(int)cub->map.rows && col < (int)ft_strlen(cub->map.grid[new_row]))
				player->pos.y = new_y;
		}

		cub->moves++;
		print_updated_pos(cub, player);
	}

	if (player->kbrd.key_s)
	{
		printf ("S pressed \n" );
		double new_x = player->pos.x - player->dir.x * player->move_speed;
		double new_y = player->pos.y - player->dir.y * player->move_speed;

		// Check X bounds and row length
		if (new_x >= 0 && new_x < cub->map.max_col)
		{
			int row = (int)player->pos.y;
			if (row >= 0 && row <=(int)cub->map.rows && new_x < (int)ft_strlen(cub->map.grid[row]))
				player->pos.x = new_x;
		}

		// Check Y bounds
		if (new_y >= 0 && new_y <=cub->map.rows)
		{
			int col = (int)player->pos.x;
			int new_row = (int)new_y;
			if (new_row >= 0 && new_row <=(int)cub->map.rows && col < (int)ft_strlen(cub->map.grid[new_row]))
				player->pos.y = new_y;
		}

		cub->moves++;
		print_updated_pos(cub, player);
	}

	if (player->kbrd.key_d)
	{
		printf ("D pressed \n" );
		double new_x = player->pos.x - player->dir.y * player->move_speed;
		double new_y = player->pos.y + player->dir.x * player->move_speed;

		// Check X bounds and row length
		if (new_x >= 0 && new_x < cub->map.max_col)
		{
			int row = (int)player->pos.y;
			if (row >= 0 && row <=(int)cub->map.rows && new_x < (int)ft_strlen(cub->map.grid[row]))
				player->pos.x = new_x;
		}

		// Check Y bounds
		if (new_y >= 0 && new_y <=cub->map.rows)
		{
			int col = (int)player->pos.x;
			int new_row = (int)new_y;
			if (new_row >= 0 && new_row <=(int)cub->map.rows && col < (int)ft_strlen(cub->map.grid[new_row]))
				player->pos.y = new_y;
		}

		cub->moves++;
		print_updated_pos(cub, player);
	}

	if (player->kbrd.key_a)
	{
		printf ("A pressed \n" );
		double new_x = player->pos.x + player->dir.y * player->move_speed;
		double new_y = player->pos.y - player->dir.x * player->move_speed;

		// Check X bounds and row length
		if (new_x >= 0 && new_x < cub->map.max_col)
		{
			int row = (int)player->pos.y;
			if (row >= 0 && row <=(int)cub->map.rows && new_x < (int)ft_strlen(cub->map.grid[row]))
				player->pos.x = new_x;
		}

		// Check Y bounds
		if (new_y >= 0 && new_y <=cub->map.rows)
		{
			int col = (int)player->pos.x;
			int new_row = (int)new_y;
			if (new_row >= 0 && new_row <=(int)cub->map.rows && col < (int)ft_strlen(cub->map.grid[new_row]))
				player->pos.y = new_y;
		}

		cub->moves++;
		print_updated_pos(cub, player);
		cub->print_debug_cub = true;
	}

	if (player->kbrd.key_left)
	{
		printf ("left arrow pressed \n" );
		double	oldDirX = player->dir.x;
		player->dir.x = player->dir.x * cos(- player->rot_speed) - player->dir.y * sin(- player->rot_speed);
		player->dir.y = oldDirX * sin(- player->rot_speed) + player->dir.y * cos(-player->rot_speed);

		double	oldPlaneX = player->plane.x;
		player->plane.x = player->plane.x * cos( - player->rot_speed) - player->plane.y * sin( - player->rot_speed);
		player->plane.y = oldPlaneX * sin(- player->rot_speed) + player->plane.y * cos(- player->rot_speed);
		cub->moves++;
		print_updated_pos(cub, player);
	}

	if (player->kbrd.key_right)
	{
		printf ("right arrow pressed \n" );
		double	oldDirX = player->dir.x;
		player->dir.x = player->dir.x * cos(player->rot_speed) - player->dir.y * sin(player->rot_speed);
		player->dir.y = oldDirX * sin(player->rot_speed) + player->dir.y * cos(player->rot_speed);

		double	oldPlaneX = player->plane.x;
		player->plane.x = player->plane.x * cos(player->rot_speed) - player->plane.y * sin(player->rot_speed);
		player->plane.y = oldPlaneX * sin(player->rot_speed) + player->plane.y * cos(player->rot_speed);
		cub->moves++;
		print_updated_pos(cub, player);
	}
}

void	move_forward(t_cub *cub, t_player *player)
{
			printf ("W pressed \n" );
		double strafeX = COLLISION_OFFSET * player->dir.x + player->dir.x * player->move_speed;
		double strafeY = COLLISION_OFFSET * player->dir.y + player->dir.y * player->move_speed;

		if (player->pos.x + player->dir.x * player->move_speed >= 1 && player->pos.x + player->dir.x * player->move_speed < cub->map.max_col
			&& cub->map.grid[(int)player->pos.y][(int)(player->pos.x + strafeX)] != '1')
			player->pos.x += player->dir.x * player->move_speed;
		if (player->pos.y + player->dir.y * player->move_speed >= 1 && player->pos.y + player->dir.x * player->move_speed < cub->map.rows
			&& cub->map.grid[(int)(player->pos.y + strafeY)][(int)player->pos.x] != '1')
			player->pos.y += player->dir.y * player->move_speed;
		cub->moves++;
		print_updated_pos(cub, player);
}

void	move_backward(t_cub *cub, t_player *player)
{
		printf ("S pressed \n" );
		double strafeX = COLLISION_OFFSET * player->dir.x + player->dir.x * player->move_speed;
		double strafeY = COLLISION_OFFSET * player->dir.y + player->dir.y * player->move_speed;

		if (player->pos.x - player->dir.x * player->move_speed >= 1 && player->pos.x - player->dir.x * player->move_speed < cub->map.max_col
				&& cub->map.grid[(int)player->pos.y][(int)(player->pos.x - strafeX)] != '1')
			player->pos.x -= player->dir.x * player->move_speed;
		if (player->pos.y - player->dir.y * player->move_speed >= 1 && player->pos.y - player->dir.x * player->move_speed < cub->map.rows
				&& cub->map.grid[(int)(player->pos.y - strafeY)][(int)player->pos.x] != '1')
			player->pos.y -= player->dir.y * player->move_speed;
		cub->moves++;
		print_updated_pos(cub, player);
}

void	strafe_right(t_cub *cub, t_player *player)
{
		printf ("D pressed \n" );

		// Move perpendicular to the right: use (dir.y, -dir.x)
		double strafeX = (COLLISION_OFFSET * -player->dir.y) + (-player->dir.y * player->move_speed);
		double strafeY = COLLISION_OFFSET * player->dir.x + player->dir.x * player->move_speed;

		if (player->pos.x + strafeX >= 1 && player->pos.x + strafeX < cub->map.max_col
				&& cub->map.grid[(int)player->pos.y][(int)(player->pos.x + strafeX)] != '1')
			player->pos.x += -player->dir.y * player->move_speed;
		if (player->pos.y + strafeY >= 1 && player->pos.y + strafeY < cub->map.rows
				&& cub->map.grid[(int)(player->pos.y + strafeY)][(int)player->pos.x] != '1')
			player->pos.y += player->dir.x * player->move_speed;
		cub->moves++;
		print_updated_pos(cub, player);
}

void	strafe_left(t_cub *cub, t_player *player)
{
	// Move perpendicular to the left: use (-dir.y, dir.x)
		printf ("A pressed \n" );

		double moveX = player->dir.y * player->move_speed;
		double moveY = -player->dir.x * player->move_speed;

		double strafeX = COLLISION_OFFSET * player->dir.y + moveX;
		double strafeY = COLLISION_OFFSET * -player->dir.x + moveY;

		if (player->pos.x + strafeX >= 1 && player->pos.x + strafeX < cub->map.max_col
				&& cub->map.grid[(int)player->pos.y][(int)(player->pos.x + strafeX)] != '1')
			player->pos.x += moveX;
		if (player->pos.y + strafeY >= 1 && player->pos.y + strafeY < cub->map.rows
				&& cub->map.grid[(int)(player->pos.y + strafeY)][(int)player->pos.x] != '1')
			player->pos.y += moveY;
		cub->moves++;
		print_updated_pos(cub, player);
		cub->print_debug_cub = true;
}

void	turn_around(t_cub *cub, t_player *player, char dir)
{
	if (dir == 'L')
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
		cub->moves++;
		print_updated_pos(cub, player);
	}

	if (dir == 'R')
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
		cub->moves++;
		print_updated_pos(cub, player);
	}
}

void	handle_move(t_cub *cub, t_player *player)
{
	if (player->kbrd.key_w)
	{
		move_forward(cub, player);
		// printf ("W pressed \n" );
		// double strafeX = COLLISION_OFFSET * player->dir.x + player->dir.x * player->move_speed;
		// double strafeY = COLLISION_OFFSET * player->dir.y + player->dir.y * player->move_speed;

		// if (player->pos.x + player->dir.x * player->move_speed >= 1 && player->pos.x + player->dir.x * player->move_speed < cub->map.max_col
		// 	&& cub->map.grid[(int)player->pos.y][(int)(player->pos.x + strafeX)] != '1')
		// 	player->pos.x += player->dir.x * player->move_speed;
		// if (player->pos.y + player->dir.y * player->move_speed >= 1 && player->pos.y + player->dir.x * player->move_speed < cub->map.rows
		// 	&& cub->map.grid[(int)(player->pos.y + strafeY)][(int)player->pos.x] != '1')
		// 	player->pos.y += player->dir.y * player->move_speed;
		// cub->moves++;
		// print_updated_pos(cub, player);
	}

	if (player->kbrd.key_s)
	{
		move_backward(cub, player);
		// printf ("S pressed \n" );
		// double strafeX = COLLISION_OFFSET * player->dir.x + player->dir.x * player->move_speed;
		// double strafeY = COLLISION_OFFSET * player->dir.y + player->dir.y * player->move_speed;

		// if (player->pos.x - player->dir.x * player->move_speed >= 1 && player->pos.x - player->dir.x * player->move_speed < cub->map.max_col
		// 		&& cub->map.grid[(int)player->pos.y][(int)(player->pos.x - strafeX)] != '1')
		// 	player->pos.x -= player->dir.x * player->move_speed;
		// if (player->pos.y - player->dir.y * player->move_speed >= 1 && player->pos.y - player->dir.x * player->move_speed < cub->map.rows
		// 		&& cub->map.grid[(int)(player->pos.y - strafeY)][(int)player->pos.x] != '1')
		// 	player->pos.y -= player->dir.y * player->move_speed;
		// cub->moves++;
		// print_updated_pos(cub, player);

	}
	if (player->kbrd.key_d)
	{
		strafe_right(cub, player);
		// printf ("D pressed \n" );

		// // Move perpendicular to the right: use (dir.y, -dir.x)
		// double strafeX = (COLLISION_OFFSET * -player->dir.y) + (-player->dir.y * player->move_speed);
		// double strafeY = COLLISION_OFFSET * player->dir.x + player->dir.x * player->move_speed;

		// if (player->pos.x + strafeX >= 1 && player->pos.x + strafeX < cub->map.max_col
		// 		&& cub->map.grid[(int)player->pos.y][(int)(player->pos.x + strafeX)] != '1')
		// 	player->pos.x += -player->dir.y * player->move_speed;
		// if (player->pos.y + strafeY >= 1 && player->pos.y + strafeY < cub->map.rows
		// 		&& cub->map.grid[(int)(player->pos.y + strafeY)][(int)player->pos.x] != '1')
		// 	player->pos.y += player->dir.x * player->move_speed;
		// cub->moves++;
		// print_updated_pos(cub, player);
	}

	if (player->kbrd.key_a)
	{
		strafe_left(cub, player);
		// // Move perpendicular to the left: use (-dir.y, dir.x)
		// printf ("A pressed \n" );

		// double moveX = player->dir.y * player->move_speed;
		// double moveY = -player->dir.x * player->move_speed;

		// double strafeX = COLLISION_OFFSET * player->dir.y + moveX;
		// double strafeY = COLLISION_OFFSET * -player->dir.x + moveY;

		// if (player->pos.x + strafeX >= 1 && player->pos.x + strafeX < cub->map.max_col
		// 		&& cub->map.grid[(int)player->pos.y][(int)(player->pos.x + strafeX)] != '1')
		// 	player->pos.x += moveX;
		// if (player->pos.y + strafeY >= 1 && player->pos.y + strafeY < cub->map.rows
		// 		&& cub->map.grid[(int)(player->pos.y + strafeY)][(int)player->pos.x] != '1')
		// 	player->pos.y += moveY;
		// cub->moves++;
		// print_updated_pos(cub, player);
		// cub->print_debug_cub = true;
	}
	if (player->kbrd.key_left)
	{
		turn_around(cub, player, 'L');
	// 	printf ("left arrow pressed \n" );
	// 	//	Matrice de rotation 2D
	// 	double	oldDirX = player->dir.x;
	// 	player->dir.x = player->dir.x * cos(- player->rot_speed) - player->dir.y * sin(- player->rot_speed);
	// 	player->dir.y = oldDirX * sin(- player->rot_speed) + player->dir.y * cos(-player->rot_speed);

	// 	//	Matrice de rotation 2D
	// 	double	oldPlaneX = player->plane.x;
	// 	player->plane.x = player->plane.x * cos( - player->rot_speed) - player->plane.y * sin( - player->rot_speed);
	// 	player->plane.y = oldPlaneX * sin(- player->rot_speed) + player->plane.y * cos(- player->rot_speed);
	// 	cub->moves++;
	// 	print_updated_pos(cub, player);
	}

	if (player->kbrd.key_right)
	{
		turn_around(cub, player, 'R');
	// 	printf ("right arrow pressed \n" );
	// 	//	Matrice de rotation 2D
	// 	double	oldDirX = player->dir.x;
	// 	player->dir.x = player->dir.x * cos(player->rot_speed) - player->dir.y * sin(player->rot_speed);
	// 	player->dir.y = oldDirX * sin(player->rot_speed) + player->dir.y * cos(player->rot_speed);

	// 	//	Matrice de rotation 2D
	// 	double	oldPlaneX = player->plane.x;
	// 	player->plane.x = player->plane.x * cos(player->rot_speed) - player->plane.y * sin(player->rot_speed);
	// 	player->plane.y = oldPlaneX * sin(player->rot_speed) + player->plane.y * cos(player->rot_speed);
	// 	cub->moves++;
	// 	print_updated_pos(cub, player);
	}



}
