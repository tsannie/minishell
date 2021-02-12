/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:37:38 by tsannie           #+#    #+#             */
/*   Updated: 2021/01/04 14:53:11 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *search, size_t len)
{
	size_t	i;
	size_t	e;

	if (search[0] == '\0')
		return ((char *)s1);
	i = 0;
	while (s1[i] && i < len)
	{
		e = 0;
		while ((s1[i + e] && search[e] && s1[i + e] == search[e]
			&& (i + e) < len))
			e++;
		if (!search[e])
			return ((char *)&s1[i]);
		i++;
	}
	return (NULL);
}
