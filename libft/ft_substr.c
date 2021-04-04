/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:29:25 by tsannie           #+#    #+#             */
/*   Updated: 2021/01/04 14:47:24 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	e;
	char	*res;
	char	*src;

	if (!s || !(res = malloc(sizeof(char) * len + 1)))
		return (NULL);
	src = (char *)s;
	i = 0;
	e = 0;
	while (s[e])
	{
		if (i < len && e >= start)
		{
			res[i] = src[i + start];
			i++;
		}
		e++;
	}
	res[len] = '\0';
	return (res);
}
