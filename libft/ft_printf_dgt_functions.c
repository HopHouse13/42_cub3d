/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:54:31 by tjacquel          #+#    #+#             */
/*   Updated: 2024/09/20 18:08:58 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbrf(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		return (ft_putstrf("-2147483648"));
	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
		count += ft_putnbrf(n / 10);
	count += ft_putcharf((n % 10) + '0');
	return (count);
}

int	ft_putunbrf(unsigned int n)
{
	unsigned int	count;

	count = 0;
	if (n > 9)
		count += ft_putunbrf(n / 10);
	count += ft_putcharf((n % 10) + '0');
	return (count);
}

int	ft_puthexadecimal_lowercase(unsigned long n)
{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789abcdef";
	if (n >= 16)
		count += ft_puthexadecimal_lowercase(n / 16);
	count += ft_putcharf(base[n % 16]);
	return (count);
}

int	ft_puthexadecimal_uppercase(unsigned long n)
{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789ABCDEF";
	if (n >= 16)
		count += ft_puthexadecimal_uppercase(n / 16);
	count += ft_putcharf(base[n % 16]);
	return (count);
}

int	ft_putaddress(void *ptr)
{
	if (ptr == NULL)
		return (ft_putstrf("(nil)"));
	ft_putstr_fd("0x", 1);
	return (ft_puthexadecimal_lowercase((unsigned long)ptr) + 2);
}
