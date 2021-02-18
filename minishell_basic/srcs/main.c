/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:46:19 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/18 12:43:32 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

void int_handler(int sig)
{
	signal(sig, SIG_IGN); // ??????
}

void disp_prompt(void)
{
	ft_putstr_fd("{MINISHELL}$> ", 1);
}

int main(int ac, char **av, char **envp)
{
	t_set *set;
	char buff[4096 + 1];

	if (!(set = malloc(sizeof(t_set))))
		return (-1);
    set->pwd = getcwd(buff, 4097);
	set->cmd = NULL;
	set->shlvl = 1;
	ft_init_env(set, envp, av);
	if (ac == 3)		// for testeur
	{
		set->exit_val = 0;
		start_shell(ac, av, set);
	}
	else
	{
		set->exit_val = 0;
		while (set->exit_val == 0)
		{
			disp_prompt();
			signal(SIGINT, int_handler);
			start_shell(ac, av, set);
		}
	}
	free(set);
	return (set->exit_val);
}
