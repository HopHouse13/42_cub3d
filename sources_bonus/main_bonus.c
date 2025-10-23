/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:27:42 by pbret             #+#    #+#             */
/*   Updated: 2025/10/23 02:20:50 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (printf("Error\ninvalid number of parameters\n"));
	parsing(&cub, argv[1]);
	exec_launch(&cub);
	exit_door(&cub, OK, NULL);
	return (0);
}
