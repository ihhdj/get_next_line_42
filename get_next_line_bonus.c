/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:07:39 by ihhadjal          #+#    #+#             */
/*   Updated: 2024/11/25 10:05:41 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_extract(char *stash)
{
	int		i;
	int		j;
	char	*nouvelle_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free (stash);
		return (NULL);
	}
	nouvelle_stash = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	i++;
	j = 0;
	while (stash[i])
	{
		nouvelle_stash[j] = stash[i];
		j++;
		i++;
	}
	free (stash);
	nouvelle_stash[j] = '\0';
	return (nouvelle_stash);
}

char	*ft_ligne(char *stash)
{
	char	*str;
	int		i;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		str[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		str[i] = '\n';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*free_all(char	*str, char	*stash)
{
	free (str);
	free (stash);
	return (NULL);
}

char	*ft_read(int fd, char *stash)
{
	char	*tmp;
	char	*str;
	int		lu;

	if (!stash)
		stash = ft_strdup("");
	lu = 1;
	str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	while (!ft_strchr(stash, '\n') && lu != 0)
	{
		lu = read(fd, str, BUFFER_SIZE);
		if (lu == -1)
			return (free_all(str, stash));
		str[lu] = '\0';
		tmp = ft_strjoin(stash, str);
		free(stash);
		stash = tmp;
	}
	free(str);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = ft_read(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = ft_ligne(stash[fd]);
	stash[fd] = ft_extract(stash[fd]);
	if (line[0] == '\0')
	{
		free (stash[fd]);
		free (line);
		return (NULL);
	}
	return (line);
}
