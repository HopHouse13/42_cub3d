/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:20:17 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/12 17:23:35 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	printf("S1 -> %sS2 -> %s\nvalue n -> %zd\n\n", s1, s2, n);
	fflush(stdout);
	size_t	i;

	 if (n == 0)
	 	return (0);
	i = 0;
	while (s1[i] && s1[i] == s2[i] && i < (n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
