/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbret <pbret@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:27:42 by pbret             #+#    #+#             */
/*   Updated: 2025/10/17 16:09:25 by pbret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (printf("Error\ninvalid number of parameters\n"));
	init_err_msgs(&cub);
	parsing(&cub, argv[1]);
	print_cub_data(&cub);
	exec_launch(&cub);
	exit_door(&cub, OK, NULL);
	return (0);
}
