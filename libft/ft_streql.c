/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_streql.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:01:28 by tsannie           #+#    #+#             */
/*   Updated: 2021/02/13 16:43:25 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_streql(const char *s1, const char *s2)
{
	int i;
	int n;

	n = (int)ft_strlen(s1);
	if (n != (int)ft_strlen(s2))
		return (-1);
	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	return (1);
}
