/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:49:56 by tjacquel          #+#    #+#             */
/*   Updated: 2024/06/11 20:19:32 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	d = (char *)dest;
	s = (char *)src;
	if (n == 0 || dest == src)
		return (dest);
	if (src > dest)
		ft_memcpy(dest, src, n);
	else
	{
		i = 0;
		while (i < n)
		{
		d[n - i - 1] = s[n - i - 1];
		i++;
		}
	}
	return ((char *)dest);
}
