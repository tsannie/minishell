/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:18:32 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/16 15:26:35 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int ft_pwd(t_set *set)
{
    char *cwd;
    char buff[4096 + 1];

/* 	if (ft_streql(set->cmd, "pwd") != 1)
	{
		ft_putstr_not_found(set->cmd);
		set->exit_val = 127; // a retirer 
		return (1);
	} */
    cwd = getcwd(buff, 4097);
    printf("%s\n",cwd);
    return (0);
}
