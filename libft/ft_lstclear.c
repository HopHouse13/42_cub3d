/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:50:27 by tjacquel          #+#    #+#             */
/*   Updated: 2025/01/08 17:57:10 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// new version 2025

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current != NULL)
	{
		tmp = current;
		current = current -> next;
		del(tmp->content);
		free(tmp);
	}
	*lst = NULL;
}

// 1. Code Structure Analysis:
// - Takes correct parameters: double pointer to list and delete function
// - Uses two pointers for safe traversal (current and tmp)
// - Has proper NULL checks at start
// - Sets list to NULL at end

// 2. Algorithm Steps:
// - Store head in current pointer
// - While traversing:
// 		a) Save current node in tmp
// 		b) Move current to next node
// 		c) Delete content using del function
// 		d) Free the tmp node
// - Finally set original list pointer to NULL

// 3. Evaluation:
//✓ Memory safety maintained ✓ No memory leaks
// ✓ Proper order of operations ✓ Meets all requirements from description
// ✓ Clean and readable implementation

// This is a correct implementation that:
// - Properly frees all memory
// - Handles edge cases
// - Sets pointer to NULL as required
// - Uses safe traversal technique

// It's actually better than the previous version because:
// - Clearer variable naming (current/tmp vs temp)
// - More straightforward traversal logic
// - Same efficiency but more readable

// old version

// void	ft_lstclear(t_list **lst, void (*del)(void*))
// {
// 	t_list	*temp;

// 	if (lst == NULL || del == NULL)
// 		return ;
// 	temp = *lst;
// 	while (*lst)
// 	{
// 		temp = temp->next;
// 		del ((*lst)->content);
// 		free(*lst);
// 		*lst = temp;
// 	}
// 	*lst = NULL;
// }
