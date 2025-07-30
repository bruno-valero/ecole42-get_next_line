/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:40:03 by brunofer          #+#    #+#             */
/*   Updated: 2025/07/30 18:26:37 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*empty(void)
{
	char	*result;

	result = (char *)malloc(1);
	result[0] = 0;
	return (result);
}

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
		return (empty());
	if (len < (len_str - start))
		size = len;
	else
		size = len_str - start;
	sub = (char *)malloc((size + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while ((i < size) && s[start])
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
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

char	*ft_strjoin(char *dst, char *src)
{
	int		i;
	int		len_dst;
	int		len_src;
	char	*result;

	if (!src || !src[0])
		return (ft_strdup(dst));
	if (!dst || !dst[0])
		return (ft_strdup(src));
	if ((!dst && !src) || (!src[0] && !dst[0]))
		return (ft_strdup(""));
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	result = malloc((len_dst + len_src + 1) * sizeof(char));
	while (src[i])
		dst[len_dst + i] = src[i];
	return (result);
}
