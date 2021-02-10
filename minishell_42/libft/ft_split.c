/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:21:23 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/10 11:07:05 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	only_c(char const *str, int i, char charset)
{
	while (str[i])
	{
		if (str[i] != charset)
			return (1);
		i++;
	}
	return (0);
}

static int	nbr_mots(char const *str, char charset, int len)
{
	int		i;
	int		sep;

	sep = 0;
	i = 0;
	while ((str[i]) && str[i] == charset)
		i++;
	while (str[i])
	{
		if (str[i] == charset)
		{
			sep++;
			while (str[i + 1] == charset && str[i + 1])
				i++;
		}
		i++;
	}
	if (str[len - 1] == charset)
		sep--;
	sep++;
	if (sep == 0)
		return (0);
	return (sep);
}

static char	*fill_splited(char const *str, int i, int alloc)
{
	int		x;
	char	*splited;

	x = 0;
	i--;
	if (!(splited = malloc(sizeof(char) * (alloc + 1))))
		return (0);
	while (x < alloc && str[i - alloc + x + 1])
	{
		splited[x] = str[i - alloc + x + 1];
		x++;
	}
	splited[x] = '\0';
	return (splited);
}

static char	**ft_splited(char **splited, char const *str, char charset, int len)
{
	int		i;
	int		alloc;
	int		sp;

	sp = -1;
	alloc = 0;
	i = 0;
	while (str[i] && only_c(str, i, charset) == 1)
	{
		alloc = 0;
		if (str[i] == charset || i == 0)
		{
			while (str[i] == charset && str[i])
				i++;
			while (str[i] != charset && str[i] && alloc++ > -2)
				i++;
			splited[++sp] = fill_splited(str, i, alloc);
			i--;
		}
		i++;
	}
	if ((str[len - 1] != charset) &&
	(sp + 2 == nbr_mots(str, charset, len)))
		splited[++sp] = fill_splited(str, i, alloc);
	return (splited);
}

char		**ft_split(char const *str, char c)
{
	char	**splited;
	int		len;

	len = 0;
	if (str)
		len = ft_strlen(str);
	if (len == 0)
	{
		if (!(splited = malloc(sizeof(char *) * (1))))
			return (NULL);
		splited[0] = NULL;
		return (splited);
	}
	if (!(splited = malloc(sizeof(char *) * (nbr_mots(str, c, len) + 1))))
		return (0);
	splited = ft_splited(splited, str, c, len);
	splited[nbr_mots(str, c, len)] = NULL;
	return (splited);
}
gcc first.c cub3d.a Libft/libft.a -L./minilibx-linux -lmlx -lXext -lX11 -lm
