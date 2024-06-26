/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:35:16 by azinchen          #+#    #+#             */
/*   Updated: 2024/06/13 15:35:27 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <string.h>
#include <limits.h> // is it allowed?

static char	*free_string(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
	return (NULL);
}

static size_t	find_nl(char *stash)
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

static char	*cut_up_to_nl(char *stash)
{
	char	*up_to_nl;
	int		i;

	if (!stash || stash[0] == '\0')
		return (NULL);
	up_to_nl = (char *)malloc((find_nl(stash) + 1) * sizeof(char));
	if (!up_to_nl)
		return (NULL);
	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
	{
		up_to_nl[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		up_to_nl[i] = stash[i];
		i++;
	}
	up_to_nl[i] = '\0';
	return (up_to_nl);
}

// this function is responsible for the new stash state.
// it should free the stash array if it contains only null terminator.
// the argument of this function is modifiable!
static char	*new_stash(char *stash)
{
	char	*new;
	size_t	nl;
	size_t	i;

	if (!stash)
		return (NULL);
	if (stash[0] == '\0')
		return (free_string(&stash));
	nl = find_nl(stash);
	new = (char *)malloc((ft_strlen(stash) - nl + 1) * sizeof(char));
	if (!new)
		return (free_string(&stash));
	i = 0;
	while (stash[nl] != '\0')
		new[i++] = stash[nl++];
	new[i] = '\0';
	if (new[0] == '\0')
		free_string(&new);
	free_string(&stash);
	return (new);
}

char	*get_next_line(int fd)
{
	static char		*stash;
	int				bytes;
	char			*buf;
	char			*temp;
	char			*res;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (free_string(&stash));
	bytes = 1;
	while (!ft_strchr(stash, '\n') && (bytes != 0))
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			free_string(&buf);
			return (free_string(&stash));
		}
		buf[bytes] = '\0';
		temp = ft_strjoin_stash(stash, buf);
		if (!temp)
		{
			free_string(&stash);
			return (free_string(&buf));
		}
		free_string(&stash);
		stash = temp;
	}
	free(buf);// don't need buf because reads in loop are over
	res = cut_up_to_nl(stash);
	if (!res)
		return (free_string(&stash));
	stash = new_stash(stash);
	return (res);
}
