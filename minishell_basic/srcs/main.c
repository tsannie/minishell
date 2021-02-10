/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:46:19 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/10 13:21:59 by phbarrad         ###   ########.fr       */
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

	if (!(set = malloc(sizeof(t_set))))
		return (-1);
    while (1)
    {
        disp_prompt();
        signal(SIGINT, int_handler);
		start_shell(ac, av, envp, set);
    }
	free(set);
    return (0);
}
