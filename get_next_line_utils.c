/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:40:03 by brunofer          #+#    #+#             */
/*   Updated: 2025/07/31 19:11:01 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	int		size;
	int		len_str;
	char	*sub;

	if ((!s && !start))
		return (NULL);
	len_str = ft_strlen(s);
	if (!s || (start > (unsigned int)len_str))
	{
		sub = (char *)malloc(1);
		sub[0] = 0;
		return (sub);
	}
	size = len_str - start;
	if (len < (len_str - start))
		size = len;
	sub = (char *)malloc((size + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while ((i < size) && s[start])
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

int	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;

	ptr = (char *)malloc(ft_strlen(s) + 1);
	if (!ptr)
		return (NULL);
	i = -1;
	while (s[++i])
		ptr[i] = s[i];
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		len_s1;
	int		len_s2;
	char	*result;

	if (!s2 || !s2[0])
		return (ft_strdup(s1));
	if (!s1 || !s1[0])
		return (ft_strdup(s2));
	if ((!s1 && !s2) || (!s2[0] && !s1[0]))
		return (ft_strdup(""));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	i = -1;
	while (s2[++i])
		result[len_s1 + i] = s2[i];
	return (result);
}

void	release_memory(void *ptr)
{
	unsigned char	*p;
	int				i;

	p = (unsigned char *)ptr;
	i = -1;
	while (p[++i])
		p[i] = '\0';
	free(ptr);
}
