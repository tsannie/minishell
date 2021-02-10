/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freedoublechar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:34:04 by tsannie           #+#    #+#             */
/*   Updated: 2021/02/10 16:44:56 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freedoublechar(char **str)
{
	while (*str)
	{
		free(*str);
		str++;
		ft_putstr_fd("\nfree\n", 1);
	}
	free(str);
}