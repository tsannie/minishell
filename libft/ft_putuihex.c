/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuihex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:20:52 by tsannie           #+#    #+#             */
/*   Updated: 2021/01/05 16:12:26 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

void	ft_putuihex(unsigned int src)
{
	char	out;

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
				ft_putuihex(src);
			ft_putchar_fd(out, 1);
		}
	}
}
