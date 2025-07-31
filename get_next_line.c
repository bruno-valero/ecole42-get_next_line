/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:40:10 by brunofer          #+#    #+#             */
/*   Updated: 2025/07/31 20:21:17 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

void		get_endl(char **buffer, int buffer_size, int fd);
void		clear_endl(char **static_buffer, char **buffer, int buffer_size);
static int	ft_strrchar(char *str, char c);

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*static_buffer;
	int			buffer_size;

	if (buffer)
	{
		release_memory(buffer);
		buffer = ft_strdup("");
	}
	else
		buffer = ft_strdup("");
	buffer_size = BUFFER_SIZE;
	get_endl(&buffer, buffer_size, fd);
	clear_endl(&static_buffer, &buffer, buffer_size);
	if (!ft_strlen(buffer))
		return (NULL);
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
		temp = ft_strdup(*buffer);
		release_memory(*buffer);
		*buffer = malloc((buffer_size + 1) * sizeof(char));
		read_bytes = read(fd, *buffer, buffer_size);
		(*buffer)[read_bytes] = '\0';
		if (ft_strrchar(*buffer, '\n') || !read_bytes)
			endl_found = 1;
		if (read_bytes > 0)
			joined = ft_strjoin(temp, *buffer);
		else
			joined = ft_strdup("");
		release_memory(*buffer);
		release_memory(temp);
		*buffer = joined;
	}
}

void	clear_endl(char **static_buffer, char **buffer, int buffer_size)
{
	char	*full_str;
	char	*one_line_buffer;
	int		i;

	if (!*static_buffer)
	{
		*static_buffer = malloc(1);
		(*static_buffer)[0] = '\0';
	}
	full_str = ft_strjoin(*static_buffer, *buffer);
	i = -1;
	while (full_str[++i])
		if (full_str[i] == '\n')
			break ;
	release_memory(*buffer);
	release_memory(*static_buffer);
	if (full_str[i + 1])
		*static_buffer = ft_substr(full_str, i + 1, ft_strlen(full_str));
	else
		*static_buffer = ft_strdup("");
	*buffer = ft_substr(full_str, 0, i + 1);
	release_memory(full_str);
}

static int	ft_strrchar(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

int	main(void)
{
	int	fd;

	fd = open("file.txt", O_RDONLY);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);

	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);

	get_next_line(fd);

	close(fd);
}
