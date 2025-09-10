/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:27:42 by pbret             #+#    #+#             */
/*   Updated: 2025/09/10 19:08:07 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	// struct globale
	if (argc != 2)
		return (printf("invalid\n"), 1);
	printf("number of arguments valid\n");
	parsing(argv[1]);
	int fd = open("./maps/invalid_maps/bad_elem1.cub", O_RDONLY);
	printf("%s\n", get_next_line(fd));
	return (0);
}
