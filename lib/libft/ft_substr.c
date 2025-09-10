/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:17:14 by tjacquel          #+#    #+#             */
/*   Updated: 2024/11/29 15:48:40 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Cette fonction extrait une sous-chaîne à partir d'une chaîne source,
à partir d'un index spécifique et pour une longueur donnée.
Exemple : Si tu veux obtenir une portion précise d'une chaîne,
comme un mot ou un segment de texte, tu utilises ft_substr.
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (len >= s_len - start)
		len = s_len - start;
	sub = ft_calloc((len + 1), sizeof(char));
	if (sub == 0)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
/*

facon differente decrire avec len > (ft_strlen(s + start))
au lieu de len >= s_len - start

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s) + start;
	sub = ft_calloc((len + 1), sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
*/
/*
#include <stdio.h>

int    main()
{
    char    *result;

    result = ft_substr("Coucou Aurore", 7, 6);
    printf("%s : Aurore\n", result);
    free(result);

    result = ft_substr("Coucou Aurore", 20, 5);
    printf("%s : "" \n", result);
    free(result);

    result = ft_substr("Coucou", 1, 10);
    printf("%s : oucou\n", result);
    free(result);

    result = ft_substr("Coucou", 2, 0);
    printf("%s : "" \n", result);
    free(result);

    result = ft_substr("Coucou", 0, 3);
    printf("%s : Cou\n", result);
    free(result);

    result = ft_substr("Coucou Aurore", 3, 10);
    printf("%s : cou Aurore\n", result);
    free(result);

    result = ft_substr("", 0, 5);
    printf("%s : "" \n", result);
    free(result);

    result = ft_substr("Coucou", 0, 6);
    printf("%s : Coucou\n", result);
    free(result);

    return (0);
}
*/
