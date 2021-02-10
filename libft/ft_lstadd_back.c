/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 10:41:39 by tsannie           #+#    #+#             */
/*   Updated: 2020/10/20 16:25:29 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*cpylast;

	if (*alst == NULL)
	{
		*alst = new;
	}
	else if (new)
	{
		cpylast = ft_lstlast(*alst);
		cpylast->next = new;
	}
}
