/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:37:32 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/10 18:55:46 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*gnl_update_stash(char *string);
char	*gnl_extract_line(char *string);
char	*gnl_read_line(int fd, char *string, char *buffer);
int		gnl_strlen(const char *s);
char	*gnl_strdup(const char *s);
char	*gnl_strjoin(const char *s1, const char *s2);
char	*gnl_strchr(const char *s, int c);

#endif
