/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:59:01 by phbarrad          #+#    #+#             */
/*   Updated: 2021/05/11 14:51:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void			init_term(t_set *set)
{
	if (!(set->history = malloc(sizeof(char *) * 1)))
		return ;
	set->history[0] = 0;
	set->inc_his = 0;
	set->his_pos = 0;
	set->tt_up = ft_strdup("\033[A");
	set->tt_down = ft_strdup("\033[B");
	set->tt_left = ft_strdup("\033[D");
	set->tt_right = ft_strdup("\033[C");
	set->tt_home = ft_strdup("\001");
	set->tt_end = ft_strdup("\005");
	set->tt_ctl_up = ft_strdup("\033\033[A");
	set->tt_crl_down = ft_strdup("\033\033[B");
}

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
	set->hide_envp = ft_unsethideenv(set, "OLDPWD");
	set->envp = ft_unsetenv(set, "OLDPWD");
	free(tmp2);
	free(tmp);
	init_term(set);
}

void			init_null(t_set *set)
{
	set->cmd = NULL;
	set->pathbc = NULL;
	set->lastcmd = NULL;
	set->all_path = NULL;
	set->str = NULL;
	set->edit_copy = NULL;
	set->word_tmp = NULL;
	set->dol_amb = NULL;
	set->namefile = NULL;
}

void			init_struct(t_set *set, char **envp)
{
	char		buff[4096 + 1];

	init_null(set);
	set->exit_val = 0;
	set->bleu = 0;
	set->pid = 0;
	set->ex_er = 0;
	set->fdin = -1;
	set->dell_len = 0;
	//set->dell_his = 0;
	set->fdout = -1;
	set->save_stdin = -1;
	set->save_stdout = -1;
	set->save_stdin = dup(STDIN);
	set->save_stdout = dup(STDOUT);
	reset_fd(set);
	set->envp = ft_strdup_tabl(envp);
	set->path = ft_get_path(envp);
	set->exit = 0;
	set->old_pwd = ft_strdup("OLDPWD=");
	set->pwd = ft_strjoin("PWD=", getcwd(buff, 4097));
	init_structafter(set);
}

int				init_all(t_set *set, char **envp)
{
	if (check_shlvl(set, envp) != 0)
		return (-1);
	init_struct(set, envp);
	start_term(set);
	ft_sort_dbtab(set);
	init_his(set);
	return (0);
}
