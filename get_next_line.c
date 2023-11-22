/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:00:11 by natrijau          #+#    #+#             */
/*   Updated: 2023/11/22 17:14:34 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

// get next line -------------
// renvoie une ligne lue depuis le descripteur de fichier 

// READ ---> renvoie un size_t
//    --> prend en parametre un fd , un buffer qui va stocker le nbre de nbytes lues, un size_t du nbre de bytes

//1
//stocker ce qui est lu par read dans un buffer

//2
//recuperer la valeur du buffer et la stocker dans une variable de stockage (static)

//3
//regarder dans cette variable si on a un \n

//4
//si pas de \n 
// ----> rappel read --- >retour a l etape 1 

//5
//si presence de \n
// -----> extraire la partie de la chaine qui nous interresse (avec \n) et la stocker dans une fction de stockage . exple :char *line 

//6
//variable stock a netoyer depuis le caractere suivant du premier \n trouve

//7
//get_next_line renvoie la valeur de line

//boucler tant que la variable statis stock est differente de 0

int	have_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*cut_nl_start(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i + 1] = '\0';
		i++;
	}
	return (str);
}

// modifer pour renvoyer 
char	*cut_nl_end(char *str)
{
	int		i;
	int		j;
	char	*dest;

	j = 0;
	i = ft_strlen(str);
	while (str[i] != '\n')
		i--;
	dest = ft_calloc(1, ((ft_strlen(str) - i) + 1));
	i++;
	if (!dest)
		return (NULL);
	while (str[i])
	{
		dest[j] = str[i];
		j++;
		i++;
	}
	free(str);
	return (dest);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*line;
	static char	*stock;
	ssize_t		read_size;
		line = ft_calloc(1, 1);
	if (!line)
		return (NULL);
	/*if (!fd || BUFFER_SIZE <= 0)
		return (0);*/
	while (1)
	{
		buff = ft_calloc(1, BUFFER_SIZE + 1);
		if (!buff)
			return (NULL);
		read_size = read(fd, buff, BUFFER_SIZE);
		//if (read_size < 1)
			//free all
			//verif si si stock != null
			//return 
		if (stock == NULL)
			stock = ft_substr(buff, 0, ft_strlen(buff));
		else
			stock = ft_strjoin(stock, buff);
		if (have_nl(stock) == 1)
		{
			printf("\nstock vaut %s\n",stock);
			line = ft_substr(stock, 0, ft_strlen(stock));
			stock = ft_strdup;
			line = cut_nl_start(line);
			free(buff);
			return (line);
		}
	}

	return (NULL);
}

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
	str = get_next_line(fd);
	printf("\n|get next line renvoie : |%s|\n", str);
	free(str);
	str = get_next_line(fd);
	printf("\n|2eme get next line renvoie : |%s|\n", str);
	free(str);
	str = get_next_line(fd);
	printf("\n|3eme get next line renvoie : |%s|\n", str);
	free(str);
	close(fd);
	return (0);
}
