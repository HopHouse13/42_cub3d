/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:09:52 by tjacquel          #+#    #+#             */
/*   Updated: 2024/06/12 18:08:19 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

// int	main(void)
// {
// 	t_list	*lst;
// 	t_list	*new;

// 	lst = ft_lstnew("bwlbcdb");
// 	new = ft_lstnew("hbdccb");
// 	ft_lstadd_front(&lst, new);
// 	ft_putendl_fd(lst->content, 1);
// 	ft_putendl_fd(lst->next->content, 1);
// 	return (0);
// }
