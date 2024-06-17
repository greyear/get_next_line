/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:35:41 by azinchen          #+#    #+#             */
/*   Updated: 2024/06/13 15:35:46 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdint.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
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

	if (!stash && !buf)
		return (NULL);
	res = (char *)malloc((ft_strlen(stash) + ft_strlen(buf) + 1) * sizeof(char));
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
	{
		res[i] = buf[j];//change to ++ and ++
		i++;
		j++;
	}
	res[ft_strlen(stash) + ft_strlen(buf)] = '\0';
	// if (stash) {
	// 	free(stash);
	// 	stash = NULL;
	// }
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
		return ((char *)malloc(1 * sizeof(char))); //???
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
