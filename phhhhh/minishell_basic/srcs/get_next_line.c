/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:36:09 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/25 09:19:09 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"
#include <stdio.h>

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

int          newline_check(char *stock, int read_size)
{
        int     i;

        i = 0;
        if (read_size == 0 && stock[0] == '\0')
                return (2);
        if (read_size == 0 || stock == NULL)
                return (0);
        while (stock[i] != '\0')
        {
                if (stock[i] == '\n')
                        return (1);
                i++;
        }
        return (0);
}

/* static int	read_stdin(int *keycode)
{
	*keycode = 0;
	if (read(STDIN, keycode, sizeof(int)) < 0)
		return (-1);
	return (1);
} */

int		get_next_line(int fd, char **line, t_set *set)
{
	static char	*stock;
	char		buff[BUFFER_SIZE + 1];
	int			i;
	int			res;
	//int			keycode = 0;

/*	
if ()
	int			term;
	char		*term_type;
	int ret;

	term_type = getenv("TERM");
    if (term_type == NULL)
        return (-1);
	ret = tgetent(*buff, term_type);
	if (ret != 1)
        return (-1);
	printf("[%d][%s]\n", ret, term_type);

	char *ku;
	char *kd;

	char *cl_string;
	char *cm_string;
	int auto_wrap;
	int height;
	int width;
	char *temp;
	char *BC;
	char *UP;
	char *DO;
 */	i = 0;
	if (!line || fd < 0 || BUFFER_SIZE < 1 || read(fd, buff, 0) == -1)
		return (-1);
	i = searchreturn(stock);
	if (stock && (i != -1))
		return (write_line(line, stock, i));
	while (((res = read(fd, buff, BUFFER_SIZE)) >= 0))
	{
		//if (read_stdin(&keycode) < 0)
		//		return (-1);
		//ft_putnbr_fd(keycode, STDERR);
		buff[res] = '\0';
		stock = ft_strjoin_free(stock, buff);
		i = searchreturn(stock);
 		//printf("[%s]\n", buff);
		if (ft_strcmp(buff, set->tt_up) == 0)
			return (1);
/* 		ku = tgetstr("ku", buff);
		kd = tgetstr("kd", buff);
		//cl_string = tgetstr("cl", NULL);
		cm_string = tgetstr("cm", buff);
		auto_wrap = tgetflag("am");
		height = tgetnum("li");
		width = tgetnum("co");
		temp = tgetstr("pc", buff);
		BC = tgetstr("le", buff);
		UP = tgetstr("up", buff);
		DO = tgetstr("do", buff);
		printf("\n\n\n[%s][%d][%d][%d][%s][%s]\n\nup = [%s]\n\ndo = [%s]\n\n",
		cm_string, auto_wrap,height,width,temp,BC,UP,DO); */

		if (res == 0 || buff[res - 1] != '\n')
		{
			ft_putstr_fd("  \b\b", 2);
			if (stock[0] == '\0')
			{
				stock = dup_free(stock, line);
				return (0);
			}
		}
		if (stock && (i != -1))
			return (write_line(line, stock, i));
	}
	stock = dup_free(stock, line);
	return (0);
}
