/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitbc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 21:25:36 by tsannie           #+#    #+#             */
/*   Updated: 2021/04/27 07:13:38 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

static int	be_charset(char a, char charset)
{
	if (a == charset)
		return (1);
	return (0);
}

static int	count_word(const char *str, char charset)
{
	int		n;
	int		word;
	int		i;

	i = 0;
	word = 0;
	while (str[i])
	{
		n = 0;
		while (str[i] && be_charset(str[i], charset) == 1)
			i++;
		while (str[i] && be_charset(str[i], charset) == 0)
		{
			n++;
			i++;
		}
		if (n > 0)
			word++;
	}
	return (word);
}

static void	alloc(char **res, const char *str, char charset)
{
	int		n;
	int		word;
	int		i;

	i = 0;
	word = 0;
	while (str[i])
	{
		n = 0;
		while (str[i] && be_charset(str[i], charset) == 1)
			i++;
		while (str[i] && be_charset(str[i], charset) == 0)
		{
			n++;
			i++;
		}
		if (n > 0 && str[i - 1] != '/')
			res[word] = malloc(sizeof(char) * (n + 2));
		else if (n > 0)
			res[word] = malloc(sizeof(char) * (n + 1));
		if (n > 0)
			word++;
	}
}

static void	fill(char **res, const char *str, char charset)
{
	int		n;
	int		word;
	int		i;

	i = 0;
	word = 0;
	while (str[i])
	{
		n = 0;
		while (str[i] && be_charset(str[i], charset) == 1)
			i++;
		while (str[i] && be_charset(str[i], charset) == 0)
		{
			res[word][n] = str[i];
			n++;
			i++;
		}
		if (n > 0)
		{
			rres(res, word, n, str[i - 1]);
			word++;
		}
	}
}

char		**ft_splitbc(const char *str, char charset)
{
	char	**res;

	if (str == NULL)
		return (NULL);
	if (!(res = malloc(sizeof(char *) * (count_word(str, charset) + 1))))
		return (NULL);
	alloc(res, str, charset);
	fill(res, str, charset);
	res[count_word(str, charset)] = 0;
	return (res);
}
