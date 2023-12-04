/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:34:20 by natrijau          #+#    #+#             */
/*   Updated: 2023/12/04 11:44:16 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <unistd.h>

static char	*cut_nl_start(char *str)
{
	int		i;
	char	*dest;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\0')
		{
			dest = ft_substr(str, 0, i + 1);
			return (dest);
		}
		i++;
	}
	return (ft_substr(str, 0, i));
}

static char	*cut_nl_end(char *str)
{
	unsigned int		i;
	char				*dest;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] && str[i] == '\n')
		i++;
	if (str[i] == '\0')
		dest = (NULL);
	else
		dest = ft_substr(str, i, (ft_strlen(str) - i));
	free(str);
	return (dest);
}

char	*get_line(char **buff, char **stock, int read_byte)
{
	char	*line;

	free(*buff);
	*buff = NULL;
	line = cut_nl_start(*stock);
	if (read_byte >= 0)
		*stock = cut_nl_end(*stock);
	else
	{
		free(*stock);
		*stock = NULL;
	}
	return (line);
}

void	get_stock(int read_byte, char **buff, char **stock)
{
	if (read_byte >= 0)
		(*buff)[read_byte] = '\0';
	if (*stock == NULL && **buff != '\0')
		*stock = ft_substr(*buff, 0, BUFFER_SIZE + 1);
	else if (**buff != '\0' && read_byte != 0)
		*stock = ft_strjoin(*stock, *buff);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*line;
	static char	*stock[1024];
	int			read_byte;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = ft_calloc(1, BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (1)
	{
		read_byte = read(fd, buff, BUFFER_SIZE);
		if (read_byte < 1 && !stock[fd])
		{
			free(buff);
			return (NULL);
		}
		get_stock(read_byte, &buff, &stock[fd]);
		if (have_nl(stock[fd]) == 1 || read_byte < BUFFER_SIZE)
		{
			line = get_line(&buff, &stock[fd], read_byte);
			return (line);
		}
	}
}
