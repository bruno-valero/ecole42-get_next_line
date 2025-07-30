/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:40:10 by brunofer          #+#    #+#             */
/*   Updated: 2025/07/30 17:43:21 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

void	get_endl(char **buffer, int buffer_size, int fd);
void	clear_endl(char *static_buffer, char *buffer, int buffer_size);

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*static_buffer;
	int			buffer_size;

	buffer_size = 42;
	get_endl(&buffer, buffer_size, fd);
	clear_endl(static_buffer, buffer, buffer_size);
	printf("%s", buffer);
	return (buffer);
}

void	get_endl(char **buffer, int buffer_size, int fd)
{
	char	*temp;
	char	*joined;
	int		endl_found;
	int		read_bytes;

	endl_found = 0;
	while (!endl_found)
	{
		read_bytes = 0;
		temp = *buffer;
		free(*buffer);
		*buffer = malloc((buffer_size + 1) * sizeof(char));
		read_bytes = read(fd, *buffer, buffer_size);
		if (!read_bytes)
		{
			*buffer[read_bytes] = '\0';
			endl_found = 1;
		}
		while (read_bytes-- || !endl_found)
			if (*buffer[read_bytes] == '\n')
				endl_found = 1;
		joined = ft_strjoin(temp, *buffer);
		free(*buffer);
		*buffer = joined;
	}
}

void	clear_endl(char *static_buffer, char *buffer, int buffer_size)
{
	char	*full_str;
	char	*one_line_buffer;
	int		i;

	if (!static_buffer)
	{
		static_buffer = malloc(1);
		static_buffer[0] = '\0';
	}
	full_str = ft_strjoin(static_buffer, buffer);
	i = -1;
	while (full_str[++i])
		if (full_str[i] == '\n')
			break ;
	free(buffer);
	free(static_buffer);
	static_buffer = ft_substr(full_str, i + 1, buffer_size);
	buffer = ft_substr(full_str, 0, i + 1);
}

int	main(void)
{
	int	fd;

	fd = open("file.txt", O_RDONLY);
	get_next_line(fd);
	close(fd);
}
