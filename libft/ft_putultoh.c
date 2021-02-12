/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putultoh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:45:16 by tsannie           #+#    #+#             */
/*   Updated: 2021/01/05 16:13:21 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putultoh(unsigned long src)
{
	char out;

	if (src == 0)
		ft_putchar_fd('0', 1);
	else
	{
		if (src)
		{
			if (src % 16 < 10)
				out = (src % 16) + 48;
			else
			{
				(src % 16) == 10 ? out = 'a' : 0;
				(src % 16) == 11 ? out = 'b' : 0;
				(src % 16) == 12 ? out = 'c' : 0;
				(src % 16) == 13 ? out = 'd' : 0;
				(src % 16) == 14 ? out = 'e' : 0;
				(src % 16) == 15 ? out = 'f' : 0;
			}
			src = src / 16;
			if (src)
				ft_putultoh(src);
			ft_putchar_fd(out, 1);
		}
	}
}
