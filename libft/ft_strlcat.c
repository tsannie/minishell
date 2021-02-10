/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:24:43 by tsannie           #+#    #+#             */
/*   Updated: 2020/10/12 18:09:50 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	e;
	size_t	n;

	i = 0;
	e = 0;
	n = 0;
	while (dst[i])
		i++;
	while (src[e])
		e++;
	if (size <= i)
		return (e + size);
	while (src[n] && n + i < size - 1)
	{
		dst[i + n] = src[n];
		n++;
	}
	dst[i + n] = '\0';
	return (e + i);
}
