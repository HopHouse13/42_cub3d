/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:01:42 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/13 19:19:33 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_images(t_cub *cub)
{
	// init minimap image
	cub->map_img.mlx_img = mlx_new_image(cub->mlx_pointer, cub->window_width, cub->window_height);
	cub->game_img.mlx_img = mlx_new_image(cub->mlx_pointer, WNDW_W, WNDW_H);
	if (!cub->map_img.mlx_img || !cub->game_img.mlx_img)
		cleanup_mlx(cub, MLX_IMG_ERR);
	cub->map_img.addr = mlx_get_data_addr(cub->map_img.mlx_img, &cub->map_img.bpp, &cub->map_img.line_len, &cub->map_img.endian);
	cub->game_img.addr = mlx_get_data_addr(cub->game_img.mlx_img, &cub->game_img.bpp, &cub->game_img.line_len, &cub->game_img.endian);
}

void	init_textures(t_cub *cub)
{
	size_t	i;
	int		width;
	int		height;

	i = -1;
	while (++i < 4)
		cub->txtr[i].mlx_img = NULL;
	i = 0;
	while (i < 4)
	{
		cub->txtr[i].mlx_img = mlx_xpm_file_to_image(cub->mlx_pointer, cub->elem.path[i], &width, &height);
		if (!cub->txtr[i].mlx_img)
			cleanup_mlx(cub, MLX_TXTR_ERR);
		cub->txtr[i].width = width;
		cub->txtr[i].height = height;
		cub->txtr[i].addr = mlx_get_data_addr(cub->txtr[i].mlx_img, &cub->txtr[i].bpp, &cub->txtr[i].line_len, &cub->txtr[i].endian);
		i++;
	}
}

void	init_exec_data(t_cub *cub)
{
	cub->mlx_pointer = NULL;
	cub->mlx_window = NULL;
	cub->map_img.mlx_img = NULL;
	cub->game_img.mlx_img = NULL;
	
	cub->moves = 0;
	cub->window_width = (cub->map).max_col * TILE_SIZE / MAP_RATIO;
	cub->window_height = (cub->map).rows * TILE_SIZE / MAP_RATIO;
	cub->map.display_map = true;

	cub->print_debug_cub = true;
	cub->game_init = true;
	cub->render_bool = true;

}

static void	which_starting_direction(t_player *player, char facing)
{
	if (facing == 'W')
	{
		player->dir.x = -1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = -0.66;
		// player->plane.y = -PLANE_MAG;

	}
	if (facing == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = 0.66;
		// player->plane.y = PLANE_MAG;

	}
	if (facing == 'N')
	{
		player->dir.x = 0;
		player->dir.y = -1;
		player->plane.x = 0.66;
		// player->plane.x = PLANE_MAG;
		player->plane.y = 0;
	}
	if (facing == 'S')
	{
		player->dir.x = 0;
		player->dir.y = 1;
		player->plane.x = -0.66;
		// player->plane.x = -PLANE_MAG;
		player->plane.y = 0;
	}
}

int	init_player(t_cub *cub, t_player *player)
{

	player->pos.x += 0.5;
	player->pos.y += 0.5;
	which_starting_direction(player, cub->elem.facing);

	player->start_time = date_in_ms();
	player->time = 0;
	player->old_time = 0;
	player->frame_time = 0;
	player->camera_x = 0;

	player->rot_speed = 0;
	player->move_speed = 0;


	player->kbrd.key_w = false;
	player->kbrd.key_s = false;
	player->kbrd.key_a = false;
	player->kbrd.key_d = false;
	player->kbrd.key_left = false;
	player->kbrd.key_right = false;
	player->kbrd.key_m = true;

	return (1);

}

void	init_ray_data(t_ray *ray)
{
	ray->ray_dir.x = 0;
	ray->ray_dir.y = 0;
	ray->map.x = 0;
	ray->map.y = 0;
	ray->side_dist.x = 0;
	ray->side_dist.y = 0;
	ray->delta_dist.x = 0;
	ray->delta_dist.y = 0;
	ray->step.x = 0;
	ray->step.y = 0;
	ray->perp_wall_dist = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_end = 0;
	ray->draw_start = 0;

}
