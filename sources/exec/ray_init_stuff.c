/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:01:42 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/07 19:17:44 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_images(t_cub *cub)
{
	// init minimap image
	cub->map_img.mlx_img = mlx_new_image(cub->mlx_pointer, cub->window_width, cub->window_height);
	cub->map_img.addr = mlx_get_data_addr(cub->map_img.mlx_img, &cub->map_img.bpp, &cub->map_img.line_len, &cub->map_img.endian);

	// // init background image
	// cub->background_img.mlx_img = mlx_new_image(cub->mlx_pointer, WNDW_W, WNDW_H);
	// cub->background_img.addr = mlx_get_data_addr(cub->background_img.mlx_img, &cub->background_img.bpp, &cub->background_img.line_len, &cub->background_img.endian);

	// init game images
	cub->game_img.mlx_img = mlx_new_image(cub->mlx_pointer, WNDW_W, WNDW_H);
	cub->game_img.addr = mlx_get_data_addr(cub->game_img.mlx_img, &cub->game_img.bpp, &cub->game_img.line_len, &cub->game_img.endian);


}



//void	init_textures(t_mlx_data *data)
//{

//	size_t		i;
//	const char	*textures_path[] = {P_FLOOR, P_WALL, P_EP, P_SP, P_WP, P_NP, P_EXTRA};
//	const char	*floor_ceiling_txtre_path[] = {P_GRASS, P_SKY};

//	i = 0;
//	while (i < 2)
//	{
//		data->bckgr_txtr[i] = mlx_xpm_file_to_image(data->mlx_pointer,
//			(char *)floor_ceiling_txtre_path[i], &data->img_width, &data->img_height);
//		if (!data->bckgr_txtr[i])
//		{
//			printf("Error initializing the textures\n");
//			close_window(data);
//		}
//		i++;
//	}

//	i = 0;
//	while (i < 7)
//	{
//		data->textures[i] = NULL;
//		i++;
//	}
//	i = 0;
//	while (i < 7)
//	{
//		data->textures[i] = mlx_xpm_file_to_image(data->mlx_pointer,
//				(char *)textures_path[i], &data->img_width, &data->img_height);
//		if (!data->textures[i])
//		{
//			printf("Error initializing the textures\n");
//			close_window(data);
//		}
//		i++;
//	}
//}

static void	init_map(t_map *map)
{
	size_t	i_rows;
	size_t	j_cols;
	size_t	max_cols;

	i_rows = 0;
	max_cols = 0;
	while (i_rows < map->rows)
	{
		j_cols = ft_strlen(map->grid[i_rows]);
		if (map->grid[i_rows][j_cols - 1] == '\n')
			j_cols-- ;
		if (max_cols < j_cols)
			max_cols = j_cols;
		i_rows++;
	}
	map->cols = max_cols;
}

void	init_exec_data(t_cub *cub)
{
	init_map(&(cub->map));
	cub->img_width = 0;
	cub->img_height = 0;
	cub->moves = 0;
	cub->window_width = (cub->map).cols * TILE_SIZE / 5;
	cub->window_height = (cub->map).rows * TILE_SIZE / 5;
	cub->map.display_map = true;
	cub->print_debug_cub = true;
}

static void	which_starting_direction(t_player *player, char facing)
{
	if (facing == 'W')
	{
		player->dir.x = -1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = -0.66;
	}
	if (facing == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = 0.66;
	}
	if (facing == 'N')
	{
		player->dir.x = 0;
		player->dir.y = -1;
		player->plane.x = 0.66;
		player->plane.y = 0;
	}
	if (facing == 'S')
	{
		player->dir.x = 0;
		player->dir.y = 1;
		player->plane.x = -0.66;
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
	// player->mlx_data_pointer = data;
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
	ray-> hit = 0;
	ray-> side = 0;

	ray->print_debug = true;
	ray->game_init = true;
}





