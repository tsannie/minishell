/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:34:18 by tsannie           #+#    #+#             */
/*   Updated: 2020/10/20 16:23:23 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*cpy;

	if (!lst || !f)
		return (NULL);
	res = NULL;
	cpy = NULL;
	while (lst)
	{
		if (!(cpy = ft_lstnew((f)(lst->content))))
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&res, cpy);
		lst = lst->next;
	}
	return (res);
}
