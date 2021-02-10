/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:27:39 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/10 11:07:05 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int			ft_ncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (((unsigned char)s1[i] || (unsigned char)s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char				*ft_strnstr(const char *haystack,
					const char *needle, size_t len)
{
	size_t			dlen;

	dlen = 0;
	while (needle[dlen])
		dlen++;
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0' && len-- >= dlen)
	{
		if (*haystack == *needle && ft_ncmp(haystack, needle, dlen) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
