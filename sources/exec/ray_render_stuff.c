/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render_stuff.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:13:25 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/11 19:19:47 by tjacquel         ###   ########.fr       */
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
			img_pxl_put(&cub->map_img, x, y, 0xFFFF00);
		// if (x >= 0 && x <= WNDW_W && y>= 0 && y<= WNDW_H)
		// 	img_pxl_put(&cub->game_img, x, y, 0xFFFF00);


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

	// if (cub->print_debug_cub)
	// {
	// 	print_ray_info(ray, x, fp);
	// 	fprintf(fp, "		Ray[%d]->start.x =		%.4f		start.y =			%.4f\n", x, start.x, start.y);
	// 	fprintf(fp, "		Ray[%d]->wall_hit.x =	%.4f		wall_hit.y =		%.4f\n\n", x, wall_hit.x, wall_hit.y);
	// }

	start.x = ((start.x * TILE_SIZE) / MAP_RATIO);
	start.y = ((start.y * TILE_SIZE) / MAP_RATIO);
	wall_hit.x = ((wall_hit.x * TILE_SIZE) / MAP_RATIO);
	wall_hit.y = ((wall_hit.y * TILE_SIZE) / MAP_RATIO);



	// Draw the ray to the exact wall hit position
	draw_ray_line(cub,
		start.x, start.y,
		wall_hit.x, wall_hit.y);
	// draw_ray_line(cub, start_screen_x, start_screen_y, end_screen_x, end_screen_y);

}


static void	verLine(t_cub *cub, int x, int draw_start, int draw_end)
{

	int	y = 0;

	while (y < draw_start) // put SKY background
	{
		img_pxl_put(&cub->game_img, x, y, cub->elem.c_color);
		y++;
	}
	y = draw_end;
	while (y < WNDW_H)
	{
		img_pxl_put(&cub->game_img, x, y, cub->elem.f_color);
		y++;
	}
	// while (draw_start < draw_end)
	// {
	// 	img_pxl_put(&cub->game_img, x, draw_start, color);
	// 	draw_start++;
	// }

}


void	render_cubes(t_cub *cub, t_player *player, t_ray *ray, int x)
{
	double	wallX;

	// int color = RGB_RED;
	ray->line_height = (int)(WNDW_H / ray->perp_wall_dist);

	ray->draw_start = -ray->line_height / 2 + WNDW_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WNDW_H / 2;
	if (ray->draw_end >= WNDW_H)
		ray->draw_end = WNDW_H - 1;


	if (ray->side) // le mur est un cote (est-ouest)
	{
		wallX = player->pos.x + ray->perp_wall_dist * ray->ray_dir.x;
		wallX -= floor((wallX));
		// if (cub->print_debug_cub)
		// 	printf("Ray[%d] wallX = %.4f\n", x, wallX);
		if (ray->step.y == 1) // WEST facing wall -- on regarde a l'est		// ca c'est le sud au final (face nord du mur // on regarde au sud)
		{
			// color = RGB_BLUE;
			texture_function(cub, player, ray, &(cub->txtr[2]), x, wallX);
		}

		else 				// EAST facing wall -- on regarde a l'ouest	// ca c'est le nord au final (face sud du mur // on regarde au nord)
		{
			// color = RGB_RED;
			texture_function(cub, player, ray, &(cub->txtr[0]), x, wallX);
		}
	}
	else // le mur n'est pas un cote (est-ouest)
	{
		wallX = player->pos.y + ray->perp_wall_dist * ray->ray_dir.y;
		wallX -= floor((wallX));
		// if (cub->print_debug_cub)
		// 	printf("Ray[%d] wallX = %.4f\n", x, wallX);
		if (ray->step.x == 1) // NORTH facing wall -- on regarde au sud // ca c'est l'est au final (face ouest du mur // on regarde a l'est)
		{
			// color = RGB_GRN;
			texture_function(cub, player, ray, &(cub->txtr[1]), x, wallX);

		}
		else // SOUTH facing wall -- on regarde au nord		// ca c'est l'ouest au final (face est du mur // on regarde a l'ouest)
		{
			// color = RGB_YLW;
			texture_function(cub, player, ray, &(cub->txtr[3]), x, wallX);
		}
	}


	verLine(cub, x, ray->draw_start, ray->draw_end);







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
			int screen_x = x * TILE_SIZE / MAP_RATIO;
			int screen_y = y * TILE_SIZE / MAP_RATIO;
			if (char_to_tile(cub->map.grid[y][x]) == TILE_WALL)
				render_sqr(&cub->map_img, (t_sqr){screen_x, screen_y, TILE_SIZE / MAP_RATIO, RGB_RED});

			else
				render_sqr(&cub->map_img, (t_sqr){screen_x, screen_y, TILE_SIZE/ MAP_RATIO, 0x0000067});			// render_tile(cub, char_to_tile(cub->map.grid[y][x]), x, y);
		}
	}

	// raycasting_loop(cub, player);
}


void	raycasting_loop(t_cub *cub, t_player *player, t_ray *ray)
{

	// int	w = cub->map.max_col;
	int	w = WNDW_W;
	// int w = 30;
	FILE	*fp;
	//int dda = 0;

	if (cub->print_debug_cub)
	{
		fp = fopen("output.txt", "w");
		if (fp == NULL)
		{
			perror("fopen");
			close_window(cub);
			cleanup_mlx(cub, MLX_OTHER_ERR);
		}
	}


	for (int x = 0; x < w; x++)
	{
		// if (cub->print_debug_cub)
		// 	print_ray_info(ray, x, fp);
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
		// if (cub->print_debug_cub)
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
		// if (cub->print_debug_cub)
		// {
		// 	printf("ray->side_dist.x = %f\n", ray->side_dist.x);
		// 	printf("ray->side_dist.y = %f\n", ray->side_dist.y);
		// }


		// DDA - Digital Differential Analyzer
		// int dda = 0;	// pour les prints de debug
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
			// if (cub->print_debug_cub)
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


		// 	// render_map(player->mlx_data_pointer, player);
		// 	render_2Dray(cub, player, ray, x, fp);
		// }

		render_cubes(cub, player, ray, x);


		if (player->kbrd.key_m == true)
		{


		// 	// render_map(cub, player);
			render_2Dray(cub, player, ray, x, fp);
		}

	}
	if (cub->print_debug_cub)
		fclose(fp);
	cub->print_debug_cub = false;
	// cub->render_bool = false;


}



int	render_loop(t_cub *cub)
{
	t_ray	ray;

	// if (cub->render_bool == false)
	// 	return (0);

	init_ray_data(&ray);


	cub->player.old_time = cub->player.time;
	cub->player.time = date_in_ms() - cub->player.start_time;
	cub->player.frame_time = (cub->player.time - cub->player.old_time) / 1000.0;
	cub->player.move_speed = cub->player.frame_time * 5.0;
	cub->player.rot_speed  = cub->player.frame_time * 3.0;

	if (cub->game_init)
		print_updated_pos(cub, &(cub->player));


	handle_move(cub, &(cub->player));

	if (cub->player.kbrd.key_m == true)
		render_map(cub, &(cub->player));

	raycasting_loop(cub, &(cub->player), &ray);


	// mlx_put_image_to_window(cub->mlx_pointer, cub->mlx_window,
	// 	cub->background_img.mlx_img, 0, 0);
	mlx_put_image_to_window(cub->mlx_pointer, cub->mlx_window,
			cub->game_img.mlx_img, 0, 0);
	if (cub->player.kbrd.key_m == true)
		{mlx_put_image_to_window(cub->mlx_pointer, cub->mlx_window,
			cub->map_img.mlx_img, 10, 10);}


	return (0);
}


bool	render(t_cub *cub)
{
	cub->mlx_pointer = mlx_init();
	if (!cub->mlx_pointer)
		return (printf("MLX initialization failed\n"), false);

	cub->mlx_window = mlx_new_window(cub->mlx_pointer, WNDW_W,
			WNDW_H, "cubD3TROIT");

	if (!cub->mlx_window)
	{
		mlx_destroy_display(cub->mlx_pointer);
		free(cub->mlx_pointer);
		return (printf("Window creation failed\n"), false);
	}
	init_images(cub);
	init_textures(cub);
	// init_images(cub);

	if (cub->game_init)
		print_txtr_struct(cub->txtr);


	mlx_loop_hook(cub->mlx_pointer, &render_loop, cub);
	mlx_hook(cub->mlx_window, KeyPress, KeyPressMask, &key_press_hook, cub);
	mlx_hook(cub->mlx_window, KeyRelease, KeyReleaseMask, &key_release_hook, cub);
	mlx_hook(cub->mlx_window, DestroyNotify, NoEventMask, &mlx_loop_end, cub->mlx_pointer);
	mlx_loop(cub->mlx_pointer);

	cleanup_mlx(cub, OK);


	return (true);
}

