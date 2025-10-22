/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utilities_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:01:54 by pbret             #+#    #+#             */
/*   Updated: 2025/10/23 00:46:29 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

char	*gnl_strdup(const char *s, char **err_id)
{
	int		i;
	int		s_len;
	char	*dup;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	dup = malloc(sizeof(char) * (s_len + 1));
	if (dup == NULL)
	{
		*err_id = ALLOC_ERR;
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*gnl_strjoin(const char *s1, const char *s2, char **err_id)
{
	char	*dest;
	size_t	i;
	size_t	j;
	size_t	dest_len;

	dest_len = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(sizeof(char) * (dest_len + 1));
	if (dest == NULL)
	{
		*err_id = ALLOC_ERR;
		return (NULL);
	}
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	j = -1;
	while (s2[++j])
		dest[i + j] = s2[j];
	dest[i + j] = '\0';
	return (dest);
}
