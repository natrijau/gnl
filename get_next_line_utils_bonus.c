/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:34:37 by natrijau          #+#    #+#             */
/*   Updated: 2023/12/04 11:35:54 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	if (!s2)
		return (NULL);
	i = 0;
	j = 0;
	str = ft_calloc(1, (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	free(s1);
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (!s || start >= ft_strlen(s))
	{
		str = ft_calloc(1, 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (len > (ft_strlen(s) - start))
		str = ft_calloc(1, ((ft_strlen(s) - start) + 1));
	else
		str = ft_calloc(1, (len + 1));
	if (!str)
		return (NULL);
	while (i < len && s[start])
		str[i++] = s[start++];
	return (str);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*tab;
	size_t			i;

	i = 0;
	if (nmemb > 65535 && size > 65535)
		return (NULL);
	if (nmemb * size > 2147483647)
		return (NULL);
	tab = malloc(nmemb * size);
	if (!tab)
		return (NULL);
	while (i < (nmemb * size))
	{
		tab[i] = '\0';
		i++;
	}
	return ((void *)tab);
}

int	have_nl(char *str)
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
