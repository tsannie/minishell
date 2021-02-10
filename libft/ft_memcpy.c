/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:23:12 by tsannie           #+#    #+#             */
/*   Updated: 2021/01/04 12:37:05 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*res;
	unsigned char	*str;

	i = 0;
	res = (unsigned char *)dst;
	str = (unsigned char *)src;
	if (src == dst || n == 0)
		return (dst);
	while (i < n)
	{
		res[i] = str[i];
		i++;
	}
	return (res);
}
