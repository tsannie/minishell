/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbcharint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 17:47:31 by tsannie           #+#    #+#             */
/*   Updated: 2020/11/28 17:57:19 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbcharint(int a)
{
	int nb;
	int c;

	nb = a;
	c = 0;
	if (nb == 0)
		return (1);
	if (nb == I_MIN)
		return (11);
	if (nb < 0)
	{
		nb = -nb;
		c++;
	}
	while (nb)
	{
		nb = nb / 10;
		c++;
	}
	return (c);
}
