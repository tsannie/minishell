/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 15:50:38 by tsannie           #+#    #+#             */
/*   Updated: 2020/10/13 17:52:56 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char *res;

	if (!(res = malloc(sizeof(char) * (count * size))))
		return (NULL);
	ft_memset(res, 0, count * size);
	return (res);
}
