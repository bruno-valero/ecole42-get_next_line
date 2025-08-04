/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:40:10 by brunofer          #+#    #+#             */
/*   Updated: 2025/08/04 16:43:36 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*static_buffer[1024];
	int			buffer_size;
	int			last_read;

	last_read = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_strdup("");
	buffer_size = BUFFER_SIZE;
	get_endl(&buffer, buffer_size, fd, &last_read);
	if (last_read < 0)
		return (release_memory((void **) &static_buffer[fd], (void **) NULL));
	clear_endl(&static_buffer[fd], &buffer);
	if (!ft_strlen(buffer))
		return (
			release_memory((void **) &static_buffer[fd], (void **) &buffer)
		);
	if (last_read && !ft_strlen(static_buffer[fd]))
		release_memory((void **) &static_buffer[fd], (void **) NULL);
	return (buffer);
}

void	get_endl(char **buffer, int buffer_size, int fd, int *last_read)
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
		release_memory((void **) buffer, (void **) NULL);
		*buffer = malloc((buffer_size + 1) * sizeof(char));
		read_bytes = read(fd, *buffer, buffer_size);
		if (!read_bytes_check(read_bytes, last_read, *buffer, temp))
			return ;
		(*buffer)[read_bytes] = '\0';
		if (ft_strrchar(*buffer, '\n') || !read_bytes)
			endl_found = 1;
		if (read_bytes > 0 || temp)
			joined = ft_strjoin(temp, *buffer);
		else
			joined = ft_strdup("");
		release_memory((void **) buffer, (void **) &temp);
		*buffer = joined;
	}
}

int	read_bytes_check(int read_bytes, int *last_read,
				char *buffer, char *temp)
{
	if (read_bytes == 0)
			*last_read = 1;
	else if (read_bytes < 0)
	{
		release_memory((void **) &buffer, (void **) &temp);
		*last_read = -1;
		return (0);
	}
	return (1);
}

void	clear_endl(char **static_buffer, char **buffer)
{
	char	*full_str;
	int		i;

	if (!*static_buffer)
		*static_buffer = ft_strdup("");
	full_str = ft_strjoin(*static_buffer, *buffer);
	i = -1;
	while (full_str[++i])
		if (full_str[i] == '\n')
			break ;
	release_memory((void **) buffer, (void **) static_buffer);
	if (!ft_strlen(full_str))
	{
		*buffer = full_str;
		return ;
	}
	if (ft_strlen(full_str) > (i + 1))
		*static_buffer = ft_substr(full_str, i + 1, ft_strlen(full_str));
	else
		*static_buffer = ft_strdup("");
	*buffer = ft_substr(full_str, 0, i + 1);
	release_memory((void **) &full_str, (void **) NULL);
}

int	ft_strrchar(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

// #include <stdio.h>
// #include <fcntl.h>

// char	*print_next_line(int fd)
// {
// 	char	*result;

// 	result = get_next_line(fd);
// 	printf("'%s'", result);
// 	return (result);
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	if (!n)
// 		return (0);
// 	i = 0;
// 	while ((s1[i] && s1[i] == s2[i]) && i < n - 1)
// 		i++;
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

// void test_gnl(int fd, char *expect)
// {
// 	char	*result;
// 	int		teste_passed;

// 	result = print_next_line(fd);
// 	if (!result)
// 	{
// 		if (!expect)
// 			teste_passed = 1;
// 		else
// 			teste_passed = 0;
// 	}
// 	else
// 		teste_passed = (!ft_strncmp(expect, result, ft_strlen(expect)));
// 	if (teste_passed)
// 		printf("-->> Passou!!\n");
// 	else
// 		printf("-->> Não Passou!!\n");
// 	release_memory((void **) &result, (void **) NULL);
// }

// int	main(void)
// {
// 	int		fd;

// 	// /* 1 */ test_gnl(-1, NULL);
// 	// // /* 2 */ test_gnl(100, NULL);
// 	// fd = open("empty.txt", O_RDONLY);
// 	// close(fd);
// 	// /* 3 */ test_gnl(fd, NULL);
// 	fd = open("files/empty", O_RDWR);
// 	/* 1 */ test_gnl(1000,  NULL);
// 	/* 2 */ test_gnl(-1,  NULL);
// 	close(fd);
// 	/* 3 */ test_gnl(fd,  NULL);

// 	// title("files/empty: ")
// 	fd = open("files/empty", O_RDWR);
// 	/* 1 */ test_gnl(fd, NULL);
// 	/* 2 */ test_gnl(fd, NULL);
// 	close(fd);

// 	// title("files/nl: ")
// 	fd = open("files/nl", O_RDWR);
// 	/* 1 */ test_gnl(fd, "\n");
// 	/* 2 */ test_gnl(fd, NULL);
// 	close(fd);

// 	// title("files/41_no_nl: ")
// 	fd = open("files/41_no_nl", O_RDWR);
// 	/* 1 */ test_gnl(fd, "01234567890123456789012345678901234567890");
// 	/* 2 */ test_gnl(fd, NULL);
// 	close(fd);

// 	// title("files/41_with_nl: ")
// 	fd = open("files/41_with_nl", O_RDWR);
// 	/* 1 */ test_gnl(fd, "0123456789012345678901234567890123456789\n");
// 		 /* 2 */ test_gnl(fd, "0");
// 		/* 3 */ test_gnl(fd, NULL);
// 		close(fd);

// 	// title("files/42_no_nl: ")
// 	fd = open("files/42_no_nl", O_RDWR);
// 	/* 1 */ test_gnl(fd, "012345678901234567890123456789012345678901");
// 	/* 2 */ test_gnl(fd, NULL);
// 	close(fd);

// 	fd = open("files/multiple_nlx5", O_RDWR);
// 	/* 1 */ test_gnl(fd, "\n");
// 	/* 2 */ test_gnl(fd, "\n");
// 	/* 3 */ test_gnl(fd, "\n");
// 	/* 4 */ test_gnl(fd, "\n");
// 	/* 5 */ test_gnl(fd, "\n");
// 	/* 6 */ test_gnl(fd, NULL);
// 	close(fd);

// 	// fd = open("file.txt", O_RDONLY);
// 	// print_next_line(fd);
// 	// close(fd);
// }
