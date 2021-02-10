/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:29:10 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/10 11:07:05 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int		ft_len(char const *s1)
{
	int			i;

	i = 0;
	while (s1[i])
		i++;
	return (i);
}

static int		is_in_set(char cmp, char const *str)
{
	int			i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == cmp)
			return (1);
	}
	return (0);
}

static char		*el_null(void)
{
	char		*str;

	if (!(str = malloc(sizeof(char) * 1)))
		return (NULL);
	str[0] = 0;
	return (str);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int			i;
	int			len;
	char		*str;
	int			e;

	if (!s1 || !set)
		return ("NULL");
	len = ft_len(s1) - 1;
	i = 0;
	e = -1;
	while (is_in_set(s1[i], set) == 1)
		i++;
	if (i == len + 1)
		return (el_null());
	while (is_in_set(s1[len], set) == 1)
		len--;
	if (!(str = malloc(sizeof(char) * (len - i + 2))))
		return (NULL);
	while (i <= len)
	{
		str[++e] = s1[i];
		i++;
	}
	str[e + 1] = '\0';
	return (str);
}
