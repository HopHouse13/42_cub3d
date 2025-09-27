/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pab <pab@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:04:15 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/27 13:48:25 by pab              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_read_line(int fd, char *string, char *buffer, t_error *err_id)
{
	char	*tmp;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(string), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (string == NULL)
			string = gnl_strdup("", err_id);
		if (string == NULL)
			return (NULL);
		tmp = string;
		string = gnl_strjoin(tmp, buffer, err_id);
		free (tmp);
		if (!string)
			return (NULL);
		if (gnl_strchr(buffer, '\n'))
			break ;
	}
	return (string);
}

char	*gnl_extract_line(char *string, t_error *err_id)
{
	char	*line;
	int		i;

	if (!string || !*string)
		return (NULL);
	i = 0;
	while (string[i] != '\0' && string[i] != '\n')
		i++;
	line = malloc((i + 1 + (string[i] == '\n')) * sizeof(char));
	if (!line)
	{
		*err_id = E_ALLOC;
		free (string);
		return (NULL);
	}
	i = 0;
	while (string[i] != '\0' && string[i] != '\n')
	{
		line[i] = string[i];
		i++;
	}
	if (string[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*gnl_update_stash(char *string, t_error *err_id)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	while (string[i] != '\0' && string[i] != '\n')
		i++;
	if (string[i] == '\0')
	{
		free(string);
		return (NULL);
	}
	new_stash = malloc((gnl_strlen(string) - i) * sizeof(char));
	if (!new_stash)
	{
		*err_id = E_ALLOC;
		return (NULL);
	}
	i++;
	j = 0;
	while (string[i] != '\0')
		new_stash[j++] = string[i++];
	new_stash[j] = '\0';
	free(string);
	return (new_stash);
}

char	*get_next_line(int fd, t_error *err_id, bool exit_door)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	if(exit_door && stash)
		free(stash);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		*err_id = E_ALLOC;
		return (NULL);
	}
	stash = gnl_read_line(fd, stash, buffer, err_id);
	free(buffer);
	if (!stash)
		return (NULL);
	line = gnl_extract_line(stash, err_id);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = gnl_update_stash(stash, err_id);
	return (line);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*str;

// 	fd = open("file.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while ((str = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", str);
// 		free(str);
// 	}
// 	//printf("\n");
// 	close (fd);
// 	free(str);
// 	return (0);
// }
