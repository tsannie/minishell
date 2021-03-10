/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:18:32 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/10 11:16:49 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int ft_pwd(t_set *set)
{
    char buff[4096 + 1];

/* 	if (ft_streql(set->cmd, "pwd") != 1)
	{
		ft_putstr_not_found(set->cmd);
		set->exit_val = 127; // a retirer
		return (1);
	} */
    set->pwd = getcwd(buff, 4097);
    ft_putstr_fd(set->pwd, STDOUT);
	ft_putchar_fd('\n', STDOUT);
    return (0);
}