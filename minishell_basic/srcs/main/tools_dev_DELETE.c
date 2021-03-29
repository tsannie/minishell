/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_dev_DELETE.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 08:29:14 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/29 15:11:14 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

void	print_args(char **str)
{
	int		i;

	i = 0;
	if (!str[0])
	{
		printf("NO ARGS\n");
	}
	else
	{
		printf("args_stock : \n");
		while (str[i])
		{
			printf("- Argument %d\t:\t|%s|\n", i, str[i]);
			i++;
		}
	}
}