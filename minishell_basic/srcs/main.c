/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:46:19 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/08 10:33:34 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

volatile int run = 1;

void		disp_prompt(void)
{
	ft_putstr_fd("{MINISHELL}$> ", 1);
}

void int_handler(int sig)
{
	run = 0;
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
	set->pwd = ft_strdup(getcwd(buff, 4097));
	set->old_pwd = NULL;
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
	ft_init_env(set, envp, av);
	ft_sort_dbtab(set);
	if (ac == 3)		// for testeur
		start_shell(ac, av, set);
	else
	{
		signal(SIGINT, int_handler);
		while (set->exit == 0)
		{
			//printf("pid = %d", getpid());
			disp_prompt();
			if (run == 1)
				start_shell(ac, av, set);
			run = 1;
		}
	}
	free(set);
	return (set->exit_val);
}
