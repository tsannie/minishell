/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:36:09 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/02 15:50:35 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;
	int		globalsize;
	int		i;
	int		e;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (NULL);
	globalsize = ft_strlen(s1) + ft_strlen(s2);
	if (!(res = malloc(sizeof(char) * globalsize + 1)))
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	free(s1);
	s1 = NULL;
	e = -1;
	while (s2[++e])
		res[i + e] = s2[e];
	res[globalsize] = '\0';
	return (res);
}

int		searchreturn(char *src)
{
	int i;

	if (!src)
		return (0);
	i = 0;
	while (src[i])
	{
		if (src[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		write_line(char **line, char *stock, int i)
{
	*line = ft_substr(stock, 0, i);
	i++;
	ft_memmove(stock, stock + i, ft_strlen(stock + i) + 1);
	return (1);
}

char	*dup_free(char *stock, char **line)
{
	if (stock)
	{
		*line = ft_strdup(stock);
		free(stock);
		stock = NULL;
	}
	else
	{
		*line = ft_strdup("");
	}
	return (stock);
}

int		get_next_line(int fd, char **line)
{
	static char	*stock;
	char		buff[BUFFER_SIZE + 1];
	int			i;
	int			res;

	i = 0;
	if (!line || fd < 0 || BUFFER_SIZE < 1 || read(fd, buff, 0) == -1)
		return (-1);
	i = searchreturn(stock);
	if (stock && (i != -1))
		return (write_line(line, stock, i));
	while (((res = read(fd, buff, BUFFER_SIZE)) > 0))
	{
		buff[res] = '\0';
		stock = ft_strjoin_free(stock, buff);
		i = searchreturn(stock);
		if (stock && (i != -1))
			return (write_line(line, stock, i));
	}
	stock = dup_free(stock, line);
	return (0);
}
