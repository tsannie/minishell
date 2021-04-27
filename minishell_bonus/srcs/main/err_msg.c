/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 12:18:28 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/27 07:13:38 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

int				start_err(char *str, t_set *set)
{
	if (set->path == NULL)
		set->exit_val = 6;
	else if (ft_strlen(set->path) == 0)
		set->exit_val = 6;
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(str, STDERR);
	if (set->exit_val == 3)
	{
		ft_putstr_fd(": is a directory\n", STDERR);
		return (1);
	}
	return (0);
}

void			eellse(t_set *set)
{
	ft_putstr_fd(": command not found\n", STDERR);
	set->exit_val = 127;
}

void			ft_putstr_not_found(char *str, t_set *set)
{
	if (start_err(str, set) == 1)
		set->exit_val = 126;
	else if (set->exit_val == 4)
	{
		ft_putstr_fd(": No such file or directory\n", STDERR);
		set->exit_val = 126;
	}
	else if (set->exit_val == 6)
	{
		ft_putstr_fd(": No such file or directory\n", STDERR);
		set->exit_val = 127;
	}
	else if (set->exit_val == 5)
	{
		ft_putstr_fd(": Permission denied\n", STDERR);
		set->exit_val = 126;
	}
	else if (set->exit_val == 7)
	{
		ft_putstr_fd(": Not a directory\n", STDERR);
		set->exit_val = 126;
	}
	else
		eellse(set);
	set->bleu = 1;
}

int				ft_putstr_error_quote(t_set *set)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd("syntax error with open quotes\n", STDERR);
	set->exit_val = 2;
	set->bleu = 1;
	return (0);
}
