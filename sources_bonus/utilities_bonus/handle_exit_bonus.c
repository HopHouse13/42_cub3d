/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:37:49 by pab               #+#    #+#             */
/*   Updated: 2025/10/28 18:11:50 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

// Function that frees the 2D map array.
static void	free_map(t_cub *cub)
{
	int	i;

	if (!cub->map.grid)
		return ;
	i = 0;
	while (cub->map.grid[i])
	{
		free(cub->map.grid[i]);
		cub->map.grid[i++] = NULL;
	}
	free(cub->map.grid);
	cub->map.grid = NULL;
}

// Function that frees textures.
static void	free_elem(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 15)
	{
		if (cub->elem.path[i])
			free(cub->elem.path[i]);
	}
}

// Function that closes the file descriptor, frees the 'stash' variable in GNL
// using the input flag set to true,
// which calls the two memory cleanup functions for elements and the map.
// If err_id is OK -> return to exit the program normally.
// Otherwise -> exit with code 2.
static void	free_parsing(t_cub *cub, char *err_id)
{
	if (cub->psg.tmp_fd != -1)
		close(cub->psg.tmp_fd);
	if (cub->psg.tmp_read != -1)
		close(cub->psg.tmp_read);
	if (cub->psg.fd_file >= 0)
		close(cub->psg.fd_file);
	if (cub->psg.line)
		free(cub->psg.line);
	get_next_line(-1, &err_id, true);
	free_elem(cub);
	free_map(cub);
}

// Handles exiting the program with an optional error message.
// If 'err_id' is not OK, prints "Error" followed by the message.
// If 'item' is provided, appends it to the message.
// Frees parsing-related resources and exits with code 2 unless 'err_id' is OK.
void	exit_door(t_cub *cub, char *err_id, char *item)
{
	if (ft_strcmp(err_id, OK))
		printf("Error\n");
	printf("%s", err_id);
	if (item != NULL)
		printf(": `%s`\n", item);
	else
		printf("\n");
	free_parsing(cub, err_id);
	if (!ft_strcmp(err_id, OK))
		return ;
	exit (2);
}
