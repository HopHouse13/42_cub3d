/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:37:32 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/27 16:00:16 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../../includes/cub3d.h" // je ne comprends pas comment ce .h reconnait t_error
# include "../../includes/error.h"

char	*get_next_line(int fd, t_error *err_id, bool exit_door);
char	*gnl_update_stash(char *string, t_error *err_id);
char	*gnl_extract_line(char *string, t_error *err_id);
char	*gnl_read_line(int fd, char *string, char *buffer, t_error *err_id);
int		gnl_strlen(const char *s);
char	*gnl_strdup(const char *s, t_error *err_id);
char	*gnl_strjoin(const char *s1, const char *s2, t_error *err_id);
char	*gnl_strchr(const char *s, int c);

#endif
