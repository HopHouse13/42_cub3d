/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:31:48 by tjacquel          #+#    #+#             */
/*   Updated: 2024/06/11 21:58:14 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	num;
	char	dgt;

	num = n;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num = -num;
	}
	if (num >= 10)
		ft_putnbr_fd((num / 10), fd);
	dgt = (num % 10) + '0';
	ft_putchar_fd(dgt, fd);
}
/*
int	main(void)
{
	ft_putnbr_fd(-123, 1);
	return (0);
}
*/
