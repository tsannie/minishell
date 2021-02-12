/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbcharhex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:57:11 by tsannie           #+#    #+#             */
/*   Updated: 2020/12/02 00:35:35 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbcharhex(unsigned long src)
{
	int i;

	i = 0;
	if (src == 0)
		return (1);
	while (src)
	{
		i++;
		src = src / 16;
	}
	return (i);
}
