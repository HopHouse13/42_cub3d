/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:12:05 by tjacquel          #+#    #+#             */
/*   Updated: 2025/01/08 20:39:35 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

int	ft_printf(const char *str, ...);
int	ft_putcharf(int c);
int	ft_putstrf(char *str);
int	ft_putnbrf(int n);
int	ft_putunbrf(unsigned int n);
int	ft_puthexadecimal_lowercase(unsigned long n);
int	ft_puthexadecimal_uppercase(unsigned long n);
int	ft_putaddress(void *ptr);

#endif
