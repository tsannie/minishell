/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 16:53:35 by tsannie           #+#    #+#             */
/*   Updated: 2020/10/11 09:28:03 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == c)
			return (&str[i]);
		i--;
	}
	return (NULL);
}
