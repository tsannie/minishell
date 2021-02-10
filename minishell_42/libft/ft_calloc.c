/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:35:04 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/10 11:07:06 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void							*ft_calloc(size_t count, size_t size)
{
	char						*aloc;
	unsigned long int			i;

	i = -1;
	if (count == 0 || size == 0)
	{
		if (!(aloc = malloc(1)))
			return (NULL);
		return (aloc);
	}
	if (!(aloc = malloc(count * size)))
		return (NULL);
	while (++i < count * size)
		aloc[i] = 0;
	return ((void *)aloc);
}
