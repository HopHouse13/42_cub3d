/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:51:17 by tjacquel          #+#    #+#             */
/*   Updated: 2025/01/08 20:28:35 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_format(char specifier, va_list *ap)
{
	if (specifier == '%')
		return (ft_putcharf('%'));
	if (specifier == 'c')
		return (ft_putcharf(va_arg(*ap, int)));
	if (specifier == 's')
		return (ft_putstrf(va_arg(*ap, char *)));
	if (specifier == 'p')
		return (ft_putaddress(va_arg(*ap, void *)));
	if (specifier == 'i' || specifier == 'd')
		return (ft_putnbrf(va_arg(*ap, int)));
	if (specifier == 'u')
		return (ft_putunbrf(va_arg(*ap, unsigned int)));
	if (specifier == 'x')
		return (ft_puthexadecimal_lowercase(va_arg(*ap, unsigned int)));
	if (specifier == 'X')
		return (ft_puthexadecimal_uppercase(va_arg(*ap, unsigned int)));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		count;

	if (str == NULL)
		return (-1);
	va_start(ap, str);
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '%')
			count += ft_putcharf(str[i]);
		else
		{
			count += ft_check_format(str[i + 1], &ap);
			i++;
		}
		i++;
	}
	va_end(ap);
	return (count);
}
// #include <stdio.h>

// int	main(void)
// {
// 	int	count = 0;
// 	count = ft_printf(0);
// 	ft_printf("%d\n", count);
// 	count = printf(0);
// 	printf("%d\n", count);
// 	return (0);
// }
