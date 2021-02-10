/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:51:23 by tsannie           #+#    #+#             */
/*   Updated: 2021/01/04 14:51:28 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*res;
	unsigned char	*str;
	size_t			i;

	res = (unsigned char *)dst;
	str = (unsigned char *)src;
	if (dst || src)
	{
		i = 0;
		while (i < n)
		{
			res[i] = str[i];
			if (str[i] == (unsigned char)c)
				return (&res[i + 1]);
			i++;
		}
	}
	return (NULL);
}
