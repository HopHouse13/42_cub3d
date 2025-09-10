/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:10:33 by tjacquel          #+#    #+#             */
/*   Updated: 2024/06/11 17:42:09 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits(long nb)
{
	size_t	dgt;

	dgt = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		dgt++;
	}
	if (nb == 0)
		dgt = 1;
	while (nb > 0)
	{
		nb = nb / 10;
		dgt++;
	}
	return (dgt);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	long	num;

	num = n;
	len = count_digits(num);
	str = ft_calloc((len + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (num < 0)
		num = -num;
	while (len > 0)
	{
		str[len - 1] = num % 10 + '0';
		num = num / 10;
		len--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_itoa(123));
	return (0);
}
*/
