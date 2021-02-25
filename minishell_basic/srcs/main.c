/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:46:19 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/24 14:48:32 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

volatile int run = 1;

void int_handler(int sig)
{
	run = 0;
}

void disp_prompt(void)
{
	ft_putstr_fd("{MINISHELL}$> ", 1);
}

int main(int ac, char **av, char **envp)
{
	t_set *set;

	if (!(set = malloc(sizeof(t_set))))
		return (-1);
	ft_init_env(set, envp, av);
	if (ac == 3)		// for testeur
		start_shell(ac, av, set);
	else
	{
		signal(SIGINT, int_handler);
		while (1)
		{
			printf("pid = %d\n", getpid());
			disp_prompt();
			start_shell(ac, av, set);
			ft_hideenv(joinf("SHLVL=", ft_itoa(set->shlvl), "", ""), set);
			ft_modenv(joinf("SHLVL=", ft_itoa(set->shlvl), "", ""), set);
		}
	}
	free(set);
	return (set->exit_val);
}
