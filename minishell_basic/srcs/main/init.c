/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:59:01 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/29 15:11:14 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

/* static const t_tab	g_tab_func[] =
{
	{"\022", ft_ctrlr},
	{"\033[A", ft_go_up},
	{"\033\033[A", ft_alt_up},
	{"\033[B", ft_go_down},
	{"\033\033[B", ft_alt_down},
	{"\033[C", ft_go_right},
	{"\033\033[C", ft_alt_right},
	{"\033[D", ft_go_left},
	{"\033\033[D", ft_alt_left},
	{"\033[H", ft_home},
	{"\001", ft_home},
	{"\033[F", ft_end},
	{"\005", ft_end},
	{"\012", ft_return},
	{"\011", ft_tab},
	{"\033[3~", ft_delete},
	{"\177", ft_backspace},
	{"\004", ft_exit_term},
	{"\013", ft_cut},
	{"\031", ft_paste},
	{"\014", ft_ctrll},
	{NULL, ft_print}
}; */

void			init_term(t_set *set)
{
	if (!(set->history = malloc(sizeof(char *) * 1)))
		return ;
	set->history[0] = 0;
	set->inc_his = 0;
	set->tt_up = ft_strdup("\033[A");
	set->tt_down = ft_strdup("\033[B");
	set->tt_left = ft_strdup("\033[D");
	set->tt_right = ft_strdup("\033\033[C");
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

void			init_struct(t_set *set, char **envp)
{
	char		buff[4096 + 1];

	set->cmd = NULL;
	set->pathbc = NULL;
	set->lastcmd = NULL;
	set->all_path = NULL;
	set->str = NULL;
	set->dol_amb = NULL;
	set->word_tmp = NULL;
	set->dol_amb = NULL;
	set->namefile = NULL;
	set->exit_val = 0;
	set->bleu = 0;
	set->pid = 0;
	set->ex_er = 0;
	set->fdin = -1;
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
		//printf("[%s]\n", set->pwd);

 	free(set->tt_up);
	free(set->tt_down);
	free(set->tt_left);
	free(set->tt_right);
	free(set->tt_home);
	free(set->tt_end);
	free(set->tt_ctl_up);
	free(set->tt_crl_down);


 	ffree(set->str);
	//ffree(set->word_tmp);
	//ffree(set->dol_amb);
	//ffree(set->namefile);
	
	
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
 
	//printf("arg = [%s]\n", set->arg[0]);
	//print_args(set->envp);

	
	//print_args(set->envp);
	//printf("----[%s]\n", set->pwd);



	free(set);
	return (ret);
}
