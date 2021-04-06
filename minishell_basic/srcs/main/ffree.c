/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ffree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 12:18:28 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/06 13:16:25 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

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
	free(set->tt_up);
	free(set->tt_down);
	free(set->tt_left);
	free(set->tt_right);
	free(set->tt_home);
	free(set->tt_end);
	free(set->tt_ctl_up);
	free(set->tt_crl_down);
	ffree(set->str);
	free_all2(set);
	free(set);
	return (ret);
}
