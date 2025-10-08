/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render_stuff.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:13:25 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/08 15:54:57 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


void draw_ray_line(t_cub *cub, int x0, int y0, int x1, int y1) // a expliciter
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;
	int x = x0, y = y0;

	while (1)
	{
		if (x >= 0 && x <= cub->window_width && y>= 0 && y<= cub->window_height)
			img_pix_put(&cub->map_img, x, y, 0xFFFF00);
		// if (x >= 0 && x <= WNDW_W && y>= 0 && y<= WNDW_H)
		// 	img_pix_put(&cub->game_img, x, y, 0xFFFF00);


		if (x == x1 && y == y1) break;

		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
}

void	render_2Dray(t_cub *cub, t_player *player, t_ray *ray, int x, FILE *fp) // a expliciter
{
	(void) fp;
	(void) x;
	// Calculate the exact wall hit position
	t_vec	wall_hit;
	t_vec	start;
	// Store the starting position for ray drawing
	start.x = player->pos.x;
	start.y = player->pos.y;
	wall_hit.x = 0;
	wall_hit.y = 0;

	if (ray->side == 0) // Hit a vertical wall (x-side)
	{
		wall_hit.x = ray->map.x;
		if (ray->step.x == -1)
			wall_hit.x += 1.0; // Hit the right side of the previous cell
		wall_hit.y = player->pos.y + (wall_hit.x - player->pos.x) * ray->ray_dir.y / ray->ray_dir.x;
	}
	else // Hit a horizontal wall (y-side)
	{
		wall_hit.y = ray->map.y;
		if (ray->step.y == -1)
			wall_hit.y += 1.0; // Hit the bottom side of the previous cell
		wall_hit.x = player->pos.x + (wall_hit.y - player->pos.y) * ray->ray_dir.x / ray->ray_dir.y;
	}

	// if (ray->print_debug)
	// {
	// 	print_ray_info(ray, x, fp);
	// 	fprintf(fp, "		Ray[%d]->start.x =		%.4f		start.y =		%.4f\n", x, start.x, start.y);
	// 	fprintf(fp, "		Ray[%d]->wall_hit.x =		%.4f		wall_hit.y =		%.4f\n\n", x, wall_hit.x, wall_hit.y);
	// }
	

	// Draw the ray to the exact wall hit position
	draw_ray_line(cub,
		start.x * TILE_SIZE, start.y * TILE_SIZE,
		wall_hit.x * TILE_SIZE, wall_hit.y * TILE_SIZE);
	// draw_ray_line(cub, start_screen_x, start_screen_y, end_screen_x, end_screen_y);

}


void	verLine(t_cub *cub, int x, int drawStart, int drawEnd, int color)
{
	int	y = 0;

	while (y < drawStart) // put SKY background
	{
		img_pix_put(&cub->game_img, x, y, RGB_SKY);
		y++;
	}
	y = drawEnd;
	while (y < WNDW_H)
	{
		img_pix_put(&cub->game_img, x, y, RGB_FLR);
		y++;
	}
	while (drawStart < drawEnd)
	{
		img_pix_put(&cub->game_img, x, drawStart, color);
		drawStart++;
	}

}


void	render_cubes(t_cub *cub, t_ray *ray, int x)
{
	int color = RGB_RED;
	int	lineHeight = (int)(WNDW_H / ray->perp_wall_dist);

	int	drawStart = -lineHeight / 2 + WNDW_H / 2;
	if (drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + WNDW_H / 2;
	if (drawEnd >= WNDW_H)
		drawEnd = WNDW_H - 1;

	if (ray->side) // le mur est un cote (est-ouest)
	{
		if (ray->step.y == 1) // WEST facing wall -- on regarde a l'est
			color = RGB_BLUE;
		else
			color = RGB_RED; // EAST facing wall -- on regarde a l'ouest
	}
	else // le mur n'est pas un cote (est-ouest)
	{
		if (ray->step.x == 1) // NORTH facing wall -- on regarde au sud
			color = RGB_GRN;
		else
			color = RGB_YLW; // SOUTH facing wall -- on regarde au nord
	}
	verLine(cub, x, drawStart, drawEnd, color);







}


void	render_map(t_cub *cub, t_player *player)
{
	(void) player;
	size_t x, y;

	for (y = 0; y < cub->map.rows; y++)
	{
		size_t	row_len = ft_strlen(cub->map.grid[y]);
		for (x = 0; x < row_len; x++) // modif de condition avoir la taille de la ligne pour chaque ligne. car la map peut avoir des lignes de dimensions differentes.
		{
			if (cub->map.grid[y][x] == '\n')
				continue ;
			int screen_x = x * TILE_SIZE;
			int screen_y = y * TILE_SIZE;
			if (char_to_tile(cub->map.grid[y][x]) == E_WALL)
				render_sqr(&cub->map_img, (t_sqr){screen_x, screen_y,  TILE_SIZE, RGB_RED});

			else
				render_sqr(&cub->map_img, (t_sqr){screen_x, screen_y,  TILE_SIZE, 0x0000067});			// render_tile(cub, char_to_tile(cub->map.grid[y][x]), x, y);
		}
	}

	// raycasting_loop(cub, player);
}


void	raycasting_loop(t_cub *cub, t_player *player, t_ray *ray)
{

	// int	w = cub->map.cols;
	int	w = WNDW_W;
	// int w = 16;
	FILE	*fp;
	//int dda = 0;

	if (ray->print_debug)
	{
		fp = fopen("output.txt", "w");
		if (fp == NULL)
		{
			perror("fopen");
			close_window(cub);
			cleanup_mlx(cub);
			exit (1);
		}
	}


	for (int x = 0; x < w; x++)
	{
		//calculate ray position and direction
		player->camera_x = 2 * x / (double)w - 1; //x-coordinate in camera space
		ray->ray_dir.x = player->dir.x + player->plane.x * player->camera_x;
		ray->ray_dir.y = player->dir.y + player->plane.y * player->camera_x;

		//which box of the map we're in
		ray->map.x = (int)player->pos.x;
		ray->map.y = (int)player->pos.y;

		// printf("ray->ray_dir.x = %f\n", ray->ray_dir.x);
		// printf("ray->ray_dir.y = %f\n", ray->ray_dir.y);


		//length of ray from one x or y-side to next x or y-side --> deltaDistX || deltaDistY
		if (ray->ray_dir.x == 0)
			ray->delta_dist.x = 1e30;
		else
			ray->delta_dist.x = fabs(1 / ray->ray_dir.x);

		if (ray->ray_dir.y == 0)
			ray->delta_dist.y = 1e30;
		else
			ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
		// if (ray->print_debug)
		// {	printf("ray->delta_dist.x = %f\n", ray->delta_dist.x);
		// 	printf("ray->delta_dist.y = %f\n", ray->delta_dist.y);}

		ray->hit = 0;

		//length of ray from current position to next x or y-side --> sideDistX || sideDistY
		if (ray->ray_dir.x < 0)
		{
			ray->step.x = -1;
			ray->side_dist.x = (player->pos.x - ray->map.x) * ray->delta_dist.x;
		}
		else
		{
			ray->step.x = 1;
			ray->side_dist.x = (ray->map.x + 1.0 - player->pos.x) * ray->delta_dist.x;
		}
		if (ray->ray_dir.y < 0)
		{
			ray->step.y = -1;
			ray->side_dist.y = (player->pos.y - ray->map.y) * ray->delta_dist.y;
		}
		else
		{
			ray->step.y = 1;
			ray->side_dist.y = (ray->map.y + 1.0 - player->pos.y) * ray->delta_dist.y;
		}
		// if (ray->print_debug)
		// {
		// 	printf("ray->side_dist.x = %f\n", ray->side_dist.x);
		// 	printf("ray->side_dist.y = %f\n", ray->side_dist.y);
		// }


		// DDA - Digital Differential Analyzer
		//int dda = 0;	// pour les prints de debug
		while (ray->hit == 0)
		{
			//jump to next map sqr, either in x-direction, or in y-direction
			if (ray->side_dist.x < ray->side_dist.y)
			{
				ray->side_dist.x += ray->delta_dist.x;
				ray->map.x += ray->step.x;
				ray->side = 0;
			}
			else
			{
				ray->side_dist.y += ray->delta_dist.y;
				ray->map.y += ray->step.y;
				ray->side = 1;
			}
			// if (ray->print_debug)
			// {
			// 	fprintf(fp, "			Ray[%d] DDA[%d]		sideDistX = %.4f		sideDistY = %.4f\n", x, dda, ray->side_dist.x, ray->side_dist.y);
			// 	dda++;
			// }
			if (cub->map.grid[(int)ray->map.y][(int)ray->map.x] == '1')
				ray->hit = 1;
		}
		if (ray->side == 0)
			ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
		else
			ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;


		// if (player->kbrd.key_m == true)
		// {
		// 	// if (ray->print_debug)
		// 	// 	print_ray_info(ray, x, fp);

		// 	// render_map(player->mlx_data_pointer, player);
		// 	render_2Dray(cub, player, ray, x, fp);
		// }

		render_cubes(cub, ray, x);


		if (player->kbrd.key_m == true)
		{
			//if (ray->print_debug)
			//	print_ray_info(ray, x, fp);

		// 	// render_map(cub, player);
			render_2Dray(cub, player, ray, x, fp);
		}

	}
	if (ray->print_debug)
		fclose(fp);
	ray->print_debug = false;
	cub->print_debug_cub = false;

}



int	render_loop(t_cub *cub)
{

	t_ray	ray;

	init_ray_data(&ray);

	// (void) player;
	// int x, y;
	// int	w = cub->map.cols;
	// int	w = cub->window_width;

	// printf ("cub->player.pos.x = %.4f\n", cub->player.pos.x);
	// printf ("cub->player.pos.y = %.4f\n", cub->player.pos.y);
	cub->player.old_time = cub->player.time;
	cub->player.time = date_in_ms() - cub->player.start_time;
	cub->player.frame_time = (cub->player.time - cub->player.old_time) / 1000.0;
	// printf("cub->player.old_time = %.2f		cub->player.time = %.2f		cub->player.frame_time = %.2f	FPS = %.2f\n", cub->player.old_time, cub->player.time, cub->player.frame_time, 1.0 / cub->player.frame_time);

	cub->player.move_speed = cub->player.frame_time * 5.0;
	cub->player.rot_speed  = cub->player.frame_time * 3.0;

	// if (ray.game_init)
	// 	print_updated_pos(&(cub->player), &ray);
	handle_move(cub, &(cub->player), &ray);



	// for (y = 0; y < 8; y++)
	// {
	// 	for (x = 0; x < 8; x++)
	// 	{
	// 		render_tile(cub, char_to_tile(cub->map.grid[y][x]), x, y);
	// 	}
	// }

	// render_background(cub, player);

	if (cub->player.kbrd.key_m == true)
		render_map(cub, &(cub->player));


	raycasting_loop(cub, &(cub->player), &ray);

	// if (player->kbrd.key_m == true)
	// 	render_map(cub, player);



	// mlx_clear_window(cub->mlx_pointer, cub->mlx_window);


	// mlx_put_image_to_window(cub->mlx_pointer, cub->mlx_window,
	// 	cub->background_img.mlx_img, 0, 0);
	mlx_put_image_to_window(cub->mlx_pointer, cub->mlx_window,
			cub->game_img.mlx_img, 0, 0);
	if (cub->player.kbrd.key_m == true)
		{mlx_put_image_to_window(cub->mlx_pointer, cub->mlx_window,
			cub->map_img.mlx_img, 0, 0);}



	return (0);
}


bool	render(t_cub *cub)
{
	cub->mlx_pointer = mlx_init();
	if (!cub->mlx_pointer)
		return (printf("MLX initialization failed\n"), false);

	cub->mlx_window = mlx_new_window(cub->mlx_pointer, WNDW_W,
			WNDW_H, "raycaster");
	// cub->mlx_window = mlx_new_window(cub->mlx_pointer, WNDW_W,
	// 		WNDW_H, "raycaster");
	if (!cub->mlx_window)
	{
		mlx_destroy_display(cub->mlx_pointer);
		free(cub->mlx_pointer);
		return (printf("Window creation failed\n"), false);
	}
	//init_textures(cub);

	init_images(cub);


	mlx_loop_hook(cub->mlx_pointer, render_loop, cub);
	mlx_hook(cub->mlx_window, KeyPress, KeyPressMask, key_press_hook, cub);
	mlx_hook(cub->mlx_window, KeyRelease, KeyReleaseMask, key_release_hook, cub);
	mlx_hook(cub->mlx_window, DestroyNotify, NoEventMask, mlx_loop_end, cub->mlx_pointer);
	mlx_loop(cub->mlx_pointer);

	cleanup_mlx(cub);


	return (true);
}

