/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:07:17 by tjacquel          #+#    #+#             */
/*   Updated: 2025/01/08 18:46:23 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == NULL || f == NULL)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// old - la variable temp n'est pas necessaire

// void	ft_lstiter(t_list *lst, void (*f)(void *))
// {
// 	t_list	*temp;

// 	if (lst == NULL || f == NULL)
// 		return ;
// 	temp = lst;
// 	while (temp)
// 	{
// 		f(temp->content);
// 		temp = temp->next;
// 	}
// }
