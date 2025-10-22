/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render_stuff.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:13:25 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/23 01:24:26 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	render_background(t_cub *cub, int x, int draw_start, int draw_end)
{
	int	y;

	y = 0;
	while (y < draw_start)
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
}

/*
8. Calculating wall height on screen (line_height)
9. Vertical drawing coordinates (draw_start, draw_end)
 */
void	compute_wall_bounds(t_ray *ray)
{
	ray->line_height = (int)(WNDW_H / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WNDW_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WNDW_H / 2;
	if (ray->draw_end >= WNDW_H)
		ray->draw_end = WNDW_H - 1;
}

/* 7. Calculating perpendicular distance to the wall (perp_wall_dist)
		The value wallX represents the exact value where the wall was hit,
			not just the integer coordinates of the wall			*/
void	render_cubes(t_cub *cub, t_player *player, t_ray *ray, int x)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
	if (ray->perp_wall_dist < 0.0001)
		ray->perp_wall_dist = 0.0001;
	compute_wall_bounds(ray);
	if (ray->side)
		ray->wall_x = player->pos.x + ray->perp_wall_dist * ray->ray_dir.x;
	else
		ray->wall_x = player->pos.y + ray->perp_wall_dist * ray->ray_dir.y;
	ray->wall_x -= floor((ray->wall_x));
	print_ray_info(ray, x);
	render_texture(cub, ray, &(cub->txtr[get_texture_index(ray)]), x);
	render_background(cub, x, ray->draw_start, ray->draw_end);
}

int	render_loop(t_cub *cub)
{
	t_ray	ray;

	init_ray_data(&ray);
	init_player_time(cub, &(cub->player));
	if (cub->game_init)
		print_updated_pos(cub, &(cub->player), NULL);
	handle_move(cub, &(cub->player));
	raycasting_loop(cub, &(cub->player), &ray);
	mlx_put_image_to_window(cub->mlx_pointer, cub->mlx_window,
		cub->game_img.mlx_img, 0, 0);
	cub->game_init = false;
	return (0);
}

void	render(t_cub *cub)
{
	cub->mlx_pointer = mlx_init();
	if (!cub->mlx_pointer)
		cleanup_mlx(cub, MLX_PTR_ERR, NULL);
	cub->mlx_window = mlx_new_window(cub->mlx_pointer, WNDW_W, WNDW_H,
			"cubD3TROIT");
	if (!cub->mlx_window)
		cleanup_mlx(cub, MLX_WDW_ERR, NULL);
	init_image(cub);
	init_textures(cub);
	mlx_loop_hook(cub->mlx_pointer, &render_loop, cub);
	mlx_hook(cub->mlx_window, KeyPress, KeyPressMask, &key_press_hook, cub);
	mlx_hook(cub->mlx_window, KeyRelease, KeyReleaseMask, &key_release_hook,
		cub);
	mlx_hook(cub->mlx_window, DestroyNotify, NoEventMask, &mlx_loop_end,
		cub->mlx_pointer);
	mlx_loop(cub->mlx_pointer);
	cleanup_mlx(cub, OK, NULL);
}
