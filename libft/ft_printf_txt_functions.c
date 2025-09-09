/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_txt_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:08:15 by tjacquel          #+#    #+#             */
/*   Updated: 2024/09/21 17:14:13 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putcharf(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstrf(char *str)
{
	int	i;

	if (!str)
		return (ft_putstrf("(null)"));
	i = 0;
	while (str[i])
	{
		ft_putchar_fd(str[i], 1);
		i++;
	}
	return (i);
}
