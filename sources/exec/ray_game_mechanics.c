/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_game_mechanics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 19:10:39 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/15 23:28:07 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_forward(t_cub *cub, t_player *player, t_vec new_pos)
{
	new_pos.x = player->pos.x + player->dir.x * player->move_speed;
	new_pos.y = player->pos.y + player->dir.y * player->move_speed;
	if (is_valid_move_x(cub, player, new_pos.x))
		player->pos.x = new_pos.x;
	if (is_valid_move_y(cub, player, new_pos.y))
		player->pos.y = new_pos.y;
	print_updated_pos(cub, player, "W");
}

void	move_backward(t_cub *cub, t_player *player, t_vec new_pos)
{
	new_pos.x = player->pos.x - player->dir.x * player->move_speed;
	new_pos.y = player->pos.y - player->dir.y * player->move_speed;
	if (is_valid_move_x(cub, player, new_pos.x))
		player->pos.x = new_pos.x;
	if (is_valid_move_y(cub, player, new_pos.y))
		player->pos.y = new_pos.y;
	print_updated_pos(cub, player, "S");
}

void	strafe_right(t_cub *cub, t_player *player, t_vec new_pos)
{
	new_pos.x = player->pos.x - player->dir.y * player->move_speed;
	new_pos.y = player->pos.y + player->dir.x * player->move_speed;
	if (is_valid_move_x(cub, player, new_pos.x))
		player->pos.x = new_pos.x;
	if (is_valid_move_y(cub, player, new_pos.y))
		player->pos.y = new_pos.y;
	print_updated_pos(cub, player, "D");
}

void	strafe_left(t_cub *cub, t_player *player, t_vec new_pos)
{
	new_pos.x = player->pos.x + player->dir.y * player->move_speed;
	new_pos.y = player->pos.y - player->dir.x * player->move_speed;
	if (is_valid_move_x(cub, player, new_pos.x))
		player->pos.x = new_pos.x;
	if (is_valid_move_y(cub, player, new_pos.y))
		player->pos.y = new_pos.y;
	print_updated_pos(cub, player, "A");
}

void	handle_move(t_cub *cub, t_player *player)
{
	t_vec	new_pos;

	new_pos = (t_vec){0, 0};
	if (player->kbrd.key_w)
		move_forward(cub, player, new_pos);
	if (player->kbrd.key_s)
		move_backward(cub, player, new_pos);
	if (player->kbrd.key_d)
		strafe_right(cub, player, new_pos);
	if (player->kbrd.key_a)
		strafe_left(cub, player, new_pos);
	if (player->kbrd.key_left)
		turn_left(cub, player);
	if (player->kbrd.key_right)
		turn_right(cub, player);
}
