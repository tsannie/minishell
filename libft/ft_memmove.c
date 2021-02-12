/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 10:26:37 by tsannie           #+#    #+#             */
/*   Updated: 2020/10/12 16:32:10 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t size)
{
	unsigned char	*src;
	unsigned char	*dst;

	src = (unsigned char *)source;
	dst = (unsigned char *)destination;
	if (src < dst)
	{
		while (size > 0)
		{
			size--;
			dst[size] = src[size];
		}
	}
	else
	{
		ft_memcpy(dst, src, size);
	}
	return (dst);
}
