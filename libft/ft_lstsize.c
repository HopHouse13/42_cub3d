/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:07:43 by tjacquel          #+#    #+#             */
/*   Updated: 2024/06/12 17:50:51 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

// #include <stdio.h>
// // Main function to test the ft_lstsize function
// int	main()
// {
// // Create nodes
// 	t_list *node1 = ft_lstnew("first");
// 	t_list *node2 = ft_lstnew("second");
// 	t_list *node3 = ft_lstnew("third");

// // Link nodes
// 	node1->next = node2;
// 	node2->next = node3;

// // Calculate the size of the list
// 	int size = ft_lstsize(node1);

// // Print the size
// 	printf("Size of the list: %d\n", size); // Output should be 3
// // Free allocated memory
// 	free(node1);
// 	free(node2);
// 	free(node3);

// 	return 0;
// }
