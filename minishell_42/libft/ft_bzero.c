/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:34:17 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/10 11:07:06 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void			ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	unsigned char	*t;

	t = (unsigned char *)s;
	i = -1;
	while (++i < n)
		t[i] = '\0';
}
