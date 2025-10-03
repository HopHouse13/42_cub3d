/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:27:42 by pbret             #+#    #+#             */
/*   Updated: 2025/10/03 19:13:01 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (printf("Error\ninvalid number of parameters\n"));
	init_cub_data(&cub);
	print_cub_data(&cub);
	parsing(&cub, argv[1]);
	exec_launch();
	exit_door(&cub, OK);
	return (0);
}
