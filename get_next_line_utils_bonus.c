/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:28:10 by azinchen          #+#    #+#             */
/*   Updated: 2024/06/28 16:28:15 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	char	symb;
	int		i;

	if (!s)
		return (NULL);
	symb = c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == symb)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == symb)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin_stash(char *stash, char *buf)
{
	char	*res;
	int		i;
	int		j;
	size_t	len;

	if (!stash && !buf)
		return (NULL);
	len = ft_strlen(stash) + ft_strlen(buf);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (stash && stash[i] != 0)
	{
		res[i] = stash[i];
		i++;
	}
	j = 0;
	while (buf && buf[j] != 0)
		res[i++] = buf[j++];
	res[len] = '\0';
	return (res);
}

char	*ft_substr(char *stash, unsigned int start, size_t len)
{
	size_t	i;
	size_t	left;
	char	*res;

	if (!stash)
		return (NULL);
	if ((unsigned int)ft_strlen(stash) < start)
		return ((char *)malloc(1 * sizeof(char)));
	left = ft_strlen(stash + start);
	if (left < len)
		len = left;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = stash[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

size_t	find_nl(char *stash)
{
	size_t	i;

	if (!stash)
		return (0);
	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return (i);
}
