/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 20:28:35 by tsannie           #+#    #+#             */
/*   Updated: 2020/10/12 16:26:15 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *pt1, const void *pt2, size_t size)
{
	size_t			i;
	unsigned char	*ch1;
	unsigned char	*ch2;

	if (size == 0 || pt1 == pt2)
		return (0);
	i = 0;
	ch1 = (unsigned char*)pt1;
	ch2 = (unsigned char*)pt2;
	while (i < size && ch1[i] == ch2[i])
		i++;
	if (i == size)
		return (0);
	return (ch1[i] - ch2[i]);
}
