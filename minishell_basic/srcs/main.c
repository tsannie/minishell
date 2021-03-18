/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:46:19 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/18 15:55:27 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int				g_run = 0;

void			disp_prompt(void)
{
	ft_putstr_fd("{MINISHELL}$> ", 1);
}

void			disp_prompt2(void)
{
	ft_putstr_fd("{MINISHELL}$> ", 1);
}


void			int_handler(int sig)
{
	//run = 1;
	ft_putstr_fd("\b\b  ", STDERR);
	ft_putstr_fd("\n", STDERR);
	g_run = 1;
	//set->exit_val = 1;
	//printf("r = [%d]\n", g_run);
	disp_prompt2();
}

void			init_struct(t_set *set, char **av, char **envp)
{
	char		buff[4096 + 1];
	char		*tmp;
	char		*tmp2;

	set->cmd = NULL;
	set->pathbc = NULL;
	set->lastcmd = NULL;
	set->all_path = NULL;
	set->exit_val = 0;
	set->save_stdout = dup(STDOUT);			// ok
	set->save_stdin = dup(STDIN);			// check that
	set->envp = ft_strdup_tabl(envp);
	set->path = ft_get_path(envp);
	set->exit = 0;
	set->old_pwd = ft_strjoin("OLDPWD=", "");
	set->pwd = ft_strjoin("PWD=", getcwd(buff, 4097));
	tmp = ft_strjoin("SHLVL=", set->shlvl);
	tmp2 = ft_itoa(set->exit_val);
	set->exit_v = ft_strjoin("?=", tmp2);
	set->all_path = ft_splitbc(set->path, ':');


	ft_init_env(set, envp, av);
	ft_hideenv(set->pwd, set);
	ft_modenv(set->pwd, set);
	//	$?
	ft_hideenv(set->exit_v, set);
	//ft_modenv(set->exit_v, set);
	//	$SHLVL
	ft_hideenv(tmp, set);
	ft_modenv(tmp, set);
	// $last_cmd
	//ft_hideenv(tmp, set);
	//ft_modenv(tmp, set);
	//
	free(tmp2);
	free(tmp);
}

void			add_exval(t_set *set)
{
	char *tmp;

	tmp = ft_itoa(set->exit_val);
	if (set->exit_v)
		free(set->exit_v);
	set->exit_v = ft_strjoin("?=", tmp);
	free(tmp);
	ft_hideenv(set->exit_v, set);
	//ft_modenv(set->exit_v, set);
}

int				main(int ac, char **av, char **envp)
{
	t_set	*set;

	if (!(set = malloc(sizeof(t_set))))
		return (-1);
	if (check_shlvl(set, envp) != 0)
		return (-1);
	init_struct(set, av, envp);
	ft_sort_dbtab(set);
	if (ac == 3)		// for testeur
		start_shell(ac, av, set);
	else
	{
		signal(SIGINT, int_handler);
		while (1)
		{
			//set->exit = run;
			if (g_run == 0)
				disp_prompt();
			if (ac == 3)
				set->str = av[2];		// for testeur
			else
			{
				set->str = get_val(set);
			}
			if (g_run == 1)
			{
				//printf("oui\n");
				set->exit_val = g_run;
				add_exval(set);
				g_run = 0;
			}
			//set->str[ft_strlen(set->str) - 1] = '\0';
			//printf("[%s]\n", set->str);
			treat_cmd(set);

			//set->exit_val = run;
			//printf("sx = [%d]\n", set->exit);

			//printf("ev[%d]run[%d]ex[%d]\n", set->exit_val, run, set->exit);
			/* if (ac == 3)
				set->str = av[2];		// for testeur
			else
				set->str = get_val(set);
			//set->str[ft_strlen(set->str) - 1] = '\0';
			//printf("[%s]\n", set->str);
			//printf("run1[%d]\n", g_run);


			treat_cmd(set, g_run); 			 *///if (run == 1)
			//{
			//	run = 0;
				//printf("run = [%d]\n", run);
				//set->exit_val = 1;
			//}
			//run = 0;
			//add_exval(set);
		}
		//printf("after = [%d]\n", run);
	}
	//if (set->all_path)
	//	ft_free_dbtab(set->all_path);
	free(set);
	return (set->exit_val);
}
