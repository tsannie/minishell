/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_char_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 12:57:41 by tsannie           #+#    #+#             */
/*   Updated: 2021/02/01 02:00:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_rev_char_tab(char *tab)
{
	int		b0;
	int		b1;
	char	save;
	int		size;

	size = ft_strlen(tab);
	b0 = 0;
	b1 = size - 1;
	while (b0 < b1)
	{
		save = tab[b0];
		tab[b0] = tab[b1];
		tab[b1] = save;
		b0++;
		b1--;
	}
}
