/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:18:32 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/22 14:47:07 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int			ft_pwd(t_set *set)
{
	char	buff[4096 + 1];

	set->pwd = getcwd(buff, 4097);
	ft_putstr_fd(set->pwd, STDOUT);
	ft_putchar_fd('\n', STDOUT);
	return (0);
}
