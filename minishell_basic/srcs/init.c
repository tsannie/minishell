/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:59:01 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/24 12:18:14 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

void			init_structafter(t_set *set)
{
	char		*tmp;
	char		*tmp2;

	tmp = ft_strjoin("SHLVL=", set->shlvl);
	tmp2 = ft_itoa(set->exit_val);
	set->exit_v = ft_strjoin("?=", tmp2);
	set->all_path = ft_splitbc(set->path, ':');
	ft_init_env(set);
	ft_hideenv(set->pwd, set);
	ft_modenv(set->pwd, set);
	ft_hideenv(set->exit_v, set);
	ft_hideenv(tmp, set);
	ft_modenv(tmp, set);
	ft_unsethideenv(set, "OLDPWD");
	ft_unsetenv(set, "OLDPWD");
	free(tmp2);
	free(tmp);
}

void			init_struct(t_set *set, char **envp)
{
	char		buff[4096 + 1];

	set->cmd = NULL;
	set->pathbc = NULL;
	set->lastcmd = NULL;
	set->all_path = NULL;
	set->exit_val = 0;
	set->bleu = 0;
	set->pid = 0;
	set->ex_er = 0;
	set->save_stdin = dup(STDIN);
	set->save_stdout = dup(STDOUT);
	reset_fd(set);
	set->envp = ft_strdup_tabl(envp);		// not free (leak)
	set->path = ft_get_path(envp);
	set->exit = 0;
	set->old_pwd = ft_strjoin("OLDPWD=", "");
	set->pwd = ft_strjoin("PWD=", getcwd(buff, 4097));
	init_structafter(set);
}

void			add_exval(t_set *set)
{
	char		*tmp;

	tmp = ft_itoa(set->exit_val);
	if (set->exit_v)
		free(set->exit_v);
	set->exit_v = ft_strjoin("?=", tmp);
	free(tmp);
	ft_hideenv(set->exit_v, set);
}

int				init_all(t_set *set, char **envp)
{
	if (check_shlvl(set, envp) != 0)
		return (-1);
	init_struct(set, envp);
	ft_sort_dbtab(set);
	return (0);
}

int				free_all(t_set *set, int ret)
{
	free(set);
	return (ret);
}
