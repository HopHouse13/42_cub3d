/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:27:42 by pbret             #+#    #+#             */
/*   Updated: 2025/09/10 12:34:18 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
		return (printf("invalid\n"), 1);
	printf("valid\n");
	check_file(argv[1]);
	return (0);
}
