/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_sprite_render_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:06:34 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/22 20:22:25 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	render_sp_txtr_color(t_cub *cub, t_sp_render *sp,
		t_txtr *current_frame, int sp_idx)
{
	int		color;
	double	distance;

	sp->txtr.y = (sp->pxl.y - sp->draw.start.y) * current_frame->height
		/ sp->height;
	color = *(int *)(current_frame->addr + sp->txtr.y * current_frame->line_len
			+ sp->txtr.x * current_frame->bpp / 8);
	if ((color & 0x00FFFFFF) != 0x000000)
	{
		if (FOG)
		{
			distance = sqrt(cub->sprites[sp_idx].distance);
			color = add_fog(distance, color);
		}
		img_pxl_put(&cub->game_img, sp->pxl.x, sp->pxl.y, color);
	}
}

// Render sprite x by x
// Calculate texture X coordinate
// Buffer check: only render if sprite is in front of wall
// Calculate texture Y coordinate
// Get pixel color
// Color key transparency (skip if black)
static void	render_sprite_txtr(t_cub *cub, t_sp_render *sp,
		t_txtr *current_frame, int sp_idx)
{
	int	x;
	int	y;

	x = sp->draw.start.x;
	while (x < sp->draw.end.x)
	{
		sp->txtr.x = (x - (-sp->width / 2 + sp->screen_x))
			* current_frame->width / sp->width;
		if (sp->transform.y > 0
			&& sp->transform.y < cub->buff[x].perp_wall_dist)
		{
			y = sp->draw.start.y;
			while (y < sp->draw.end.y)
			{
				sp->pxl = (t_coord){x, y};
				render_sp_txtr_color(cub, sp, current_frame, sp_idx);
				y++;
			}
		}
		x++;
	}
}

// Translate sprite position relative to camera
// Transform sprite with inverse camera matrix
// Calculate sprite screen position
// Calculate sprite dimensions
// Calculate drawing bounds
static void	compute_sprite_rendering(t_cub *cub, t_sprite *sprite,
		t_sp_render *sp)
{
	sp->rel_pos.x = sprite->pos.x - cub->player.pos.x;
	sp->rel_pos.y = sprite->pos.y - cub->player.pos.y;
	sp->inv_det = 1.0 / (cub->player.plane.x * cub->player.dir.y
			- cub->player.dir.x * cub->player.plane.y);
	sp->transform.x = sp->inv_det * (cub->player.dir.y * sp->rel_pos.x
			- cub->player.dir.x * sp->rel_pos.y);
	sp->transform.y = sp->inv_det * (-cub->player.plane.y * sp->rel_pos.x
			+ cub->player.plane.x * sp->rel_pos.y);
	sp->screen_x = (int)((WNDW_W / 2) * (1 + sp->transform.x
				/ sp->transform.y));
	sp->height = abs((int)(WNDW_H / sp->transform.y));
	sp->width = abs((int)(WNDW_H / sp->transform.y));
	sp->draw.start.y = -sp->height / 2 + WNDW_H / 2;
	if (sp->draw.start.y < 0)
		sp->draw.start.y = 0;
	sp->draw.end.y = sp->height / 2 + WNDW_H / 2;
	if (sp->draw.end.y >= WNDW_H)
		sp->draw.end.y = WNDW_H - 1;
	sp->draw.start.x = -sp->width / 2 + sp->screen_x;
	if (sp->draw.start.x < 0)
		sp->draw.start.x = 0;
	sp->draw.end.x = sp->width / 2 + sp->screen_x;
	if (sp->draw.end.x >= WNDW_W)
		sp->draw.end.x = WNDW_W - 1;
}

// Get current animation frame
// Don't render if behind player or too close
void	render_single_sprite(t_cub *cub, t_sprite *sprite, int sp_idx)
{
	t_sp_render	sp;
	t_txtr		*current_frame;

	compute_sprite_rendering(cub, sprite, &sp);
	current_frame = &cub->sp_txtr[sprite->current_frame];
	if (sp.transform.y <= 0.1)
		return ;
	render_sprite_txtr(cub, &sp, current_frame, sp_idx);
}
