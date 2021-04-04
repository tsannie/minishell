/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 07:48:57 by tsannie           #+#    #+#             */
/*   Updated: 2020/10/13 17:24:56 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*src;
	size_t			i;

	src = (unsigned char *)b;
	i = 0;
	while (len > i)
	{
		src[i] = (unsigned char)c;
		i++;
	}
	b = (void *)src;
	return (b);
}
