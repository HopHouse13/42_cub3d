/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:38:34 by tjacquel          #+#    #+#             */
/*   Updated: 2024/11/29 15:39:13 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ca buggait pour ouvrir le fichier original ca disait que cetait pas en c
// du coup jai refait un copier coller

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int			i;
	long int	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while (nptr[i] == ' ' || nptr[i] == '\f' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1 * sign;
		i++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = 10 * res + (nptr[i] - '0');
		i++;
	}
	res = sign * res;
	if (res > 2147483647 || res < -2147483648)
		return (-1);
	return ((int)res);
}
// pour proteger encore mieux
// les return values peuvent etre redefinies
// mais sinon c'est undefined behavior
// le truc qui change en gros cest sassurer que res
// depasse pas LONG_MAX avant de le multiplier par 10 et additionner
// attention il faudrait creer des helpers functions pour descendre
// en dessous de 25lignes

// int	ft_atoi(const char *nptr)
// {
// 	int			i;
// 	long int	res;
// 	int			sign;

// 	i = 0;
// 	res = 0;
// 	sign = 1;
// 	while (nptr[i] == ' ' || nptr[i] == '\f' || nptr[i] == '\n'
// 		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
// 		i++;
// 	if (nptr[i] == '+' || nptr[i] == '-')
// 	{
// 		if (nptr[i] == '-')
// 			sign = -1;
// 		i++;
// 	}
// 	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
// 	{
// 		if (res > (LONG_MAX - (nptr[i] - '0')) / 10)
// 		{
// 			if (sign == -1)
// 				return (INT_MIN);
// 			if (sign == 1)
// 				return (INT_MAX);
// 		}
// 		res = 10 * res + (nptr[i] - '0');
// 		i++;
// 	}
// 	res = sign * res;
// 	if (res > INT_MAX)
// 		return (INT_MAX);
// 	if (res < INT_MIN)
// 		return (INT_MIN);
// 	return ((int)res);
// }
