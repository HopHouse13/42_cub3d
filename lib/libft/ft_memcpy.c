/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:23:07 by tjacquel          #+#    #+#             */
/*   Updated: 2024/06/11 20:19:39 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	d = (char *)dest;
	s = (char *)src;
	i = 0;
	if (n == 0 || dest == src)
		return (dest);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return ((char *)dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char str[] = "abcdefgh";
	// Chevauchement entre src et dest
	memcpy(str + 4, str, 4);
	printf("%s\n", str);  // Le résultat est indéfini
	return (0);
}
*/
