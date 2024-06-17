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

static void	free_string(char *str)
{
	if (str)
		free(str);
}

static size_t	find_nl_index(char *stash)
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

static char	*cut_up_to_nl(char *stash) //или size_t?
{
	char	*up_to_nl;
	int		i;
	size_t	nl;

	if (!stash || stash[0] == '\0')
		return (NULL);
	nl = find_nl_index(stash);
	up_to_nl = (char *)malloc((nl + 1) * sizeof(char)); //+1 не в скобках?
	if (!up_to_nl)
	{
		// free(stash);
		// stash = NULL;
		return (NULL);
	}
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
	{
		free_string(stash);
		stash = NULL;
		return (NULL);
	}
	nl = find_nl_index(stash);
	new = (char *)malloc((ft_strlen(stash) - nl + 1) * sizeof(char));
	if (!new)
	{
		free_string(stash);
		stash = NULL;
		return (NULL);
	}
	i = 0;
	while (stash[nl] != '\0')
		new[i++] = stash[nl++];
	new[i] = '\0';
	if (new[0] == '\0')
	{
		free_string(new);
		new = NULL;
	}
	free_string(stash);
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
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	bytes = 1;
	while (!ft_strchr(stash, '\n') && (bytes != 0)) //allowed?
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			free_string(buf);
			free_string(stash);
			stash = NULL;
			return (NULL);
		}
		buf[bytes] = '\0';
		temp = ft_strjoin_stash(stash, buf);
		if (!temp)
		{
			free_string(stash);
			stash = NULL;
			free_string(buf);
			buf = NULL;
			return (NULL);
		}
		free_string(stash);
		stash = NULL;
		stash = temp;
	}
	free(buf);// don't need buf because reads in loop are over
	res = cut_up_to_nl(stash);
	if (!res)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = new_stash(stash);
	return (res);
}
