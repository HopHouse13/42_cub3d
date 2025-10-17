/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:37:49 by pab               #+#    #+#             */
/*   Updated: 2025/10/17 16:46:51 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Fonction qui libere le double tableau de la map.
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

// Fonction qui libere les 4 textures.
static void	free_elem(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (cub->elem.path[i])
			free(cub->elem.path[i]);
	}
}

// Fonction qui ferme fd_file, libere la varible 'stash' dans GNL avec le flag
// true en parametre d'entree, qui appelle les 2 fonctions de liberation de
// memoire de elem et map.
// Si err_id est a 'OK'->return pour fermer le programme avec le return du main.
// Sinon -> exit(2).
static void	free_parsing(t_cub *cub, t_error err_id)
{
	if (cub->psg.fd_file >= 0)
		close(cub->psg.fd_file);
	if (cub->psg.line)
		free(cub->psg.line);
	get_next_line(-1, &err_id, true);
	free_elem(cub);
	free_map(cub);
}

// Securite si err_id est negatif renvoie le message 'UNKNOWN_ERR'.
// Affiche "error\n" si err_id est plus grand que 'OK'.
// Affiche le message  correspondant a la valeur err_id.
// Appelle de la fonction free_parsing pour liberer les memoires.
void	exit_door(t_cub *cub, t_error err_id, char *item)
{
	if (err_id < OK)
		err_id = UNKNOWN_ERR;
	if (err_id > OK)
		printf("Error\n");
	printf("%s", cub->err_msg[err_id]);
	if (item != NULL)
		printf(" -> %s\n", item);
	else
		printf("\n");
	free_parsing(cub, err_id);
	if (err_id == OK)
		return ;
	exit (2);
}
