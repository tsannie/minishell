/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:13:12 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/10 11:07:05 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;
	unsigned char	*td;
	unsigned char	*ts;

	td = (unsigned char *)dst;
	ts = (unsigned char *)src;
	i = -1;
	if (!dst && !src)
		return (NULL);
	if (td > ts)
	{
		while (i + 1 < len)
		{
			td[len - 1] = ts[len - 1];
			len--;
		}
	}
	else
	{
		while (++i < len)
			td[i] = ts[i];
	}
	return (dst);
}
