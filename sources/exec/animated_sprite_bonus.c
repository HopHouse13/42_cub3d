/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_sprite_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:24:59 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/22 14:47:48 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void render_single_sprite(t_cub *cub, t_sprite *sprite, int sp_idx)
{
	t_vec	sprite_rel;
	t_vec	transform;
	double	inv_det;
	int		sprite_screen_x;
	int		sprite_height, sprite_width;
	t_coord	draw_start, draw_end;
	int		stripe;
	t_txtr	*current_frame;
	(void)	sp_idx;

	// Get current animation frame
	current_frame = &cub->sp_txtr[sprite->current_frame];

	// Translate sprite position relative to camera
	sprite_rel.x = sprite->pos.x - cub->player.pos.x;
	sprite_rel.y = sprite->pos.y - cub->player.pos.y;

	// Transform sprite with inverse camera matrix
	inv_det = 1.0 / (cub->player.plane.x * cub->player.dir.y
					- cub->player.dir.x * cub->player.plane.y);

	transform.x = inv_det * (cub->player.dir.y * sprite_rel.x
							- cub->player.dir.x * sprite_rel.y);
	transform.y = inv_det * (-cub->player.plane.y * sprite_rel.x
							+ cub->player.plane.x * sprite_rel.y);

	// Don't render if behind player or too close
	if (transform.y <= 0.1)
		return;

	// Calculate sprite screen position
	sprite_screen_x = (int)((WNDW_W / 2) * (1 + transform.x / transform.y));

	// Calculate sprite dimensions
	sprite_height = abs((int)(WNDW_H / transform.y));
	sprite_width = abs((int)(WNDW_H / transform.y));

	// Calculate drawing bounds
	draw_start.y = -sprite_height / 2 + WNDW_H / 2;
	if (draw_start.y < 0) draw_start.y = 0;
	draw_end.y = sprite_height / 2 + WNDW_H / 2;
	if (draw_end.y >= WNDW_H) draw_end.y = WNDW_H - 1;

	draw_start.x = -sprite_width / 2 + sprite_screen_x;
	if (draw_start.x < 0) draw_start.x = 0;
	draw_end.x = sprite_width / 2 + sprite_screen_x;
	if (draw_end.x >= WNDW_W) draw_end.x = WNDW_W - 1;

	// Render sprite stripe by stripe
	stripe = draw_start.x;
	while (stripe < draw_end.x)
	{
		// Calculate texture X coordinate
		int tex_x = (stripe - (-sprite_width / 2 + sprite_screen_x))
					* current_frame->width / sprite_width;

		// ZBuffer check: only render if sprite is in front of wall
		if (transform.y > 0 && transform.y < cub->buff[stripe].perp_wall_dist)
		{
			int y = draw_start.y;
			while (y < draw_end.y)
			{
				// Calculate texture Y coordinate
				int tex_y = (y - draw_start.y) * current_frame->height / sprite_height;

				// Get pixel color
				int color = *(int *)(current_frame->addr
							+ tex_y * current_frame->line_len
							+ tex_x * current_frame->bpp / 8);

				// Color key transparency (skip if black/magenta)
				if ((color & 0x00FFFFFF) != 0x000000)   // Not black
				{
					// color = add_fog(cub->sprites[sp_idx].distance, color);
					img_pxl_put(&cub->game_img, stripe, y, color);
				}

				y++;
			}
		}
		stripe++;
	}
}

void	sort_sprites(t_sp_render *sprites, int sprite_nb)
{
	int			i;
	int			j;
	t_sp_render	temp;

	i = 0;
	while (i < sprite_nb - 1)
	{
		j = 0;
		while (j < sprite_nb - i - 1)
		{
			if (sprites[j].distance < sprites[j + 1].distance)
			{
				temp = sprites[j];
				sprites[j] = sprites[j + 1];
				sprites[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	count_active_sprites(t_cub *cub)
{
	int	i;
	int	active_count;

	i = 0;
	active_count = 0;
	while (i < cub->elem.sprite_nb)
	{
		if (cub->sprites[i].active)
			active_count++;
		i++;
	}
	return (active_count);
}

void	render_all_sprites(t_cub *cub)
{
	t_sp_render	sp_order[MAX_SPRITES];
	int			i;
	t_vec		delta;
	int			active_sprites;

	active_sprites = 0;
	i = 0;
	while (i < cub->elem.sprite_nb)
	{
		if (cub->sprites[i].active)
		{
			delta.x = cub->sprites[i].pos.x - cub->player.pos.x;
			delta.y = cub->sprites[i].pos.y - cub->player.pos.y;
			sp_order[active_sprites].sprite_idx = i;
			sp_order[active_sprites].distance = delta.x * delta.x + delta.y * delta.y;
			cub->sprites[i].distance = sp_order[active_sprites].distance;
			active_sprites++;
		}
		i++;
	}
	sort_sprites(sp_order, active_sprites);

	i = 0;
	while (i < active_sprites)
	{
		if (cub->sprites[sp_order[i].sprite_idx].active)
			render_single_sprite(cub, &cub->sprites[sp_order[i].sprite_idx], sp_order[i].sprite_idx);
		i++;
	}
}


void	count_sprites(t_cub *cub)
{
	int		i;
	int		j;

	i = -1;
	while (cub->map.grid[++i])
	{
		j = -1;
		while (cub->map.grid[i][++j])
		{
			if (cub->map.grid[i][j] == 'C')
				cub->elem.sprite_nb++;
		}
	}
}

void	update_sprite_animation(t_sprite *sprite, double frame_time)
{
	sprite->elapsed_time += frame_time;
	if (sprite->elapsed_time >= sprite->frame_duration)
	{
		sprite->elapsed_time = 0.0;
		sprite->current_frame++;
		if (sprite->current_frame >= sprite->frame_count)
		{
			if (sprite->loop)
				sprite->current_frame = 0;
			else
				sprite->current_frame = sprite->frame_count - 1;
		}
	}
}

void	update_all_sprites(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->elem.sprite_nb)
	{
		if (cub->sprites[i].active)
			update_sprite_animation(&cub->sprites[i], cub->player.frame_time);
		// if (cub->sprites[i].distance < 0.5)
		// 	cub->sprites[i].active = false;
		if (fabs(cub->player.pos.x - cub->sprites[i].pos.x) < 0.5
			&& fabs(cub->player.pos.y - cub->sprites[i].pos.y) < 0.5)
			cub->sprites[i].active = false;
		i++;
	}
}

void	init_single_sprite(t_sprite *sprite, int x, int y)
{
	sprite->pos = (t_vec){x + 0.5, y + 0.5};
	sprite->active = true;
	sprite->frame_count = 10;
	sprite->current_frame = 0;
	sprite->frame_duration = 0.2;
	sprite->elapsed_time = 0.0;
	sprite->distance = 0.0;
	sprite->loop = true;
	sprite->action = false;
}

void		init_sprites(t_cub *cub)
{
	int	i;
	int	j;
	int	sprite_idx;

	sprite_idx = 0;
	count_sprites(cub);
	printf("count_sprites counted cub->elem.sprite_nb = %d\n", cub->elem.sprite_nb);
	if (cub->elem.sprite_nb == 0)
		return ;
	if (cub->elem.sprite_nb > MAX_SPRITES)
		cleanup_mlx(cub, MLX_OTHER_ERR);
	cub->sprites = malloc(sizeof(t_sprite) * cub->elem.sprite_nb);
	if (!cub->sprites)
		cleanup_mlx(cub, MLX_OTHER_ERR);

	i = -1;
	while (cub->map.grid[++i])
	{
		j = -1;
		while (cub->map.grid[i][++j])
		{
			if (cub->map.grid[i][j] == 'C')
			{
				init_single_sprite(&cub->sprites[sprite_idx], j, i);
				sprite_idx++;
			}
		}
	}
	print_sprites(cub);
}
