/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 18:53:40 by tsannie           #+#    #+#             */
/*   Updated: 2021/01/04 13:08:06 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	char	*str;
	size_t	i;
	size_t	e;

	e = 0;
	if (!src)
		return (0);
	str = (char *)src;
	while (str[e])
		e++;
	if (size <= 0)
		return (e);
	i = 0;
	while (str[i] && i < size - 1)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (e);
}
