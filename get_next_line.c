/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:26:27 by natrijau          #+#    #+#             */
/*   Updated: 2023/11/24 11:56:21 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static int  have_nl(char *str)
{
	int	i;
    
    if (!str)
    {
        return (0);
    }
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char *cut_nl_start(char *str)
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
	return (str);
}

static char *cut_nl_end(char *str)
{
	unsigned int		i;
	char	*dest;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] && str[i] == '\n')
		i++;
	if (str[i] == '\0')
		dest = (NULL);
	else
		dest = ft_substr(str, i, (ft_strlen(str) - i));
    //free(str);
	return (dest);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*line;
	static char	*stock;
	int			read_byte;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = ft_calloc(1, BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
    read_byte = 1;
	while (read_byte > 0)
	{
		read_byte = read(fd, buff, BUFFER_SIZE);
		if (read_byte == -1 || (read_byte == 0 && !stock))
		{
			free(buff);
			return (NULL);
		}
		if (stock == NULL && buff[0] != '\0')
			stock = ft_substr(buff, 0, BUFFER_SIZE);
		else if (buff[0] != '\0')
			stock = ft_strjoin(stock, buff);
		if (have_nl(stock) == 1 || read_byte == 0)
		{
            free(buff);
            buff = NULL;
			line = cut_nl_start(stock);
			stock = cut_nl_end(stock);
			return (line);
		}
	}
    free(buff);
    if (read_byte == '\0')
    {
        free(stock);
    }
	return (NULL);
}
/*
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int	main(int ac, char **av)
{
	int		fd;
	char	*str;

	(void)ac;
	(void)av;
	fd = open("test.txt", O_RDONLY);
    while (1)
    {
        str = get_next_line(fd);
        if (str)
            printf("%s", str);
        else
            break;
        free(str);
    }
	close(fd);
	return (0);
}*/
