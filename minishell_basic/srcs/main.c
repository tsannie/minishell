/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:46:19 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/02 13:30:39 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

volatile int run = 1;

void int_handler(int sig)
{
	run = 0;
	ft_putstr_fd("\b\b  ", STDERR);
	ft_putstr_fd("\n", STDERR);
	exit(0);
}

void		disp_prompt(void)
{
	ft_putstr_fd("{MINISHELL}$> ", 1);
}

int			main(int ac, char **av, char **envp)
{
	t_set	*set;
	char	buff[4096 + 1];

	if (!(set = malloc(sizeof(t_set))))
		return (-1);
	set->pwd = getcwd(buff, 4097);
	set->cmd = NULL;
	set->shlvl = 1;
	set->exit_val = 0;
	int e = -1;
	/* while (envp[++e])
		printf("-[%s]-\n", envp[e]);
	printf("\n\n"); */
	set->envp = ft_strdup_tabl(envp);
	set->path = ft_get_path(envp);
	//printf("[%s]\n", set->path);
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
			//printf("pid = %d\n", getpid());
			disp_prompt();
			start_shell(ac, av, set);
			//ft_hideenv(joinf("SHLVL=", ft_itoa(set->shlvl), "", ""), set);
			//ft_modenv(joinf("SHLVL=", ft_itoa(set->shlvl), "", ""), set);
		}
	}
	free(set);
	return (set->exit_val);
}
