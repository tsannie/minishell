/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:18:32 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/27 07:13:38 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

int			ft_pwd(t_set *set)
{
	char	buff[4096 + 1];

	ffree(set->pwd);
	set->pwd = ft_strdup(getcwd(buff, 4097));
	ft_putstr_fd(set->pwd, STDOUT);
	ft_putchar_fd('\n', STDOUT);
	return (0);
}
