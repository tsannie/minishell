/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ffree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 12:18:28 by phbarrad          #+#    #+#             */
/*   Updated: 2021/05/18 09:22:42 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void			ffree(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void			free_all2(t_set *set)
{
	ffree(set->pathbc);
	ffree(set->pwd);
	ffree(set->cmd);
	ffree(set->path);
	ffree(set->lastcmd);
	ffree(set->exit_v);
	ffree(set->shlvl);
	ffree(set->old_pwd);
	ft_free_dbtab(set->list);
	ft_free_dbtab(set->push);
	ft_free_dbtab(set->history);
	ft_free_dbtab(set->all_path);
	ft_free_dbtab(set->hide_envp);
	ft_free_dbtab(set->envp);
	ft_free_dbtab(set->arg);
}

int				free_all(t_set *set, int ret)
{
	ffree(set->tt_up);
	ffree(set->tt_down);
	ffree(set->tt_left);
	ffree(set->tt_right);
	ffree(set->tt_ctl_up);
	ffree(set->tt_crl_down);
	ffree(set->str);
	ffree(set->credir);
	ffree(set->edit_copy);
	free_all2(set);
	free(set);
	return (ret);
}
