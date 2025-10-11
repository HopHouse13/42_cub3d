/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 14:31:58 by pbret             #+#    #+#             */
/*   Updated: 2025/10/11 15:11:08 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// check si le fichier de path peut etre bien ouvert (creation d'un fd)
// et etre lu pour verifier si le fichier en question n'est pas un dossier.
// La lecture avec 'read' est impossible si c'etait un dossier. (renvoie -1)
static t_error	check_path(char *path)
{
	int		tmp_fd;
	int		tmp_read;
	char	tmp_buf[1];

	tmp_fd = open(path, O_RDONLY);
	if (tmp_fd == -1)
		return (E_PATH);
	tmp_read = read(tmp_fd, tmp_buf, 1);
	if (tmp_read == -1)
		return (E_READ_PATH);
	close(tmp_fd);
	return (OK);
}

// Le pointeur de line se trouve au debut du path.
// 'nb_char_path' est le nbr de char du path pour pouvoir le dup correctement.
// verification si l'espace de memoire reservee pour le path de chaque 'key_id'
// specifiquement est vide ou deja remplit(controle des doublons).
// dub et stockqge dans cub->elem.path avec la cle specifique.
// Enfin retour du retour de 'check_path' que check si le path est valide.
t_error	handle_paths(t_cub *cub, char **line, t_key key_id)
{
	unsigned int	nb_char_path;
	char			*tmp_line;

	tmp_line = *line;
	nb_char_path = 0;
	while (**line && **line != ' ' && **line != '\n')
	{
		(*line)++;
		nb_char_path++;
	}
	if (!cub->elem.path[key_id])
	{
		cub->elem.path[key_id] = ft_strndup(tmp_line, nb_char_path);
		if (!cub->elem.path[key_id])
			return (E_ALLOC);
	}
	else
		return (E_DUP_PATH);
	return (check_path(cub->elem.path[key_id]));
}
