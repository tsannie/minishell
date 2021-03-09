/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:46:19 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/09 09:09:59 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

void		disp_prompt(void)
{
	ft_putstr_fd("{MINISHELL}$> ", 1);
}

void int_handler(int sig)
{
	ft_putstr_fd("\b\b  ", STDERR);
	ft_putstr_fd("\n", STDERR);
	disp_prompt();
	//exit(0);
}

int			main(int ac, char **av, char **envp)
{
	t_set	*set;
	char	buff[4096 + 1];

	if (!(set = malloc(sizeof(t_set))))
		return (-1);
	//set->pwd = ft_strdup(getcwd(buff, 4097));
	//set->old_pwd = ft_strdup("");

	set->cmd = NULL;
	set->shlvl = 1;
	set->exit_val = 0;
	set->fd = 1;
	/*int e = -1;
	 while (envp[++e])
		printf("-[%s]-\n", envp[e]);
	printf("\n\n"); */
	//print_args(envp);
	set->envp = ft_strdup_tabl(envp);
	set->path = ft_get_path(envp);
	set->exit = 0;
	set->pid = 0;


	set->old_pwd = ft_strjoin("OLDPWD=", "");
	//set->pwd = ft_strdup(getcwd(buff, 4097));
	set->pwd = ft_strjoin("PWD=", getcwd(buff, 4097));
	ft_init_env(set, envp, av);


	ft_hideenv(set->pwd, set);
	ft_modenv(set->pwd, set);
	//ft_hideenv(set->old_pwd, set);
	//ft_modenv(set->old_pwd, set);

	free(set->old_pwd);
	free(set->pwd);
	
	ft_sort_dbtab(set);
	char *temp;


	if (ac == 3)		// for testeur
		start_shell(ac, av, set);
	else
	{
		signal(SIGINT, int_handler);
		while (set->exit == 0)
		{
			//printf("pid = %d", getpid());
			disp_prompt();
/* 			set->pwd = ft_strdup(getcwd(buff, 4097));
			temp = ft_strdup(set->pwd);
			free(set->pwd);
			set->pwd = ft_strjoin("PWD=", temp);
			free(temp);
			ft_hideenv(set->pwd, set);
			ft_modenv(set->pwd, set);
			free(set->pwd); */
			start_shell(ac, av, set);
		}
	}
	free(set);
	return (set->exit_val);
}
