/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 10:37:47 by tsannie           #+#    #+#             */
/*   Updated: 2021/01/04 13:22:36 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		be_char(char a, char *charset)
{
	size_t i;

	i = 0;
	while (charset[i])
	{
		if (a == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int		size_glob(char *src, char *charset)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(src);
	i = 0;
	while (be_char(src[len - 1], charset) == 1 && src[len - 1])
		len--;
	if (len > 0)
		while (be_char(src[i], charset) == 1)
		{
			i++;
			len--;
		}
	return (len);
}

void	filling(char *src, char *charset, char *res, size_t len)
{
	size_t	i;
	size_t	e;

	i = 0;
	e = 0;
	while (be_char(src[i], charset) == 1)
		i++;
	while (len > e)
	{
		res[e] = src[i + e];
		e++;
	}
	res[e] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	char	*src;
	char	*charset;
	size_t	len;

	src = (char *)s1;
	charset = (char *)set;
	if (!src)
		return (NULL);
	len = size_glob(src, charset);
	if (!(res = malloc(sizeof(char) * len + 1)))
		return (NULL);
	filling(src, charset, res, len);
	return (res);
}
