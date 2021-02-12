/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:46:19 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/12 13:30:26 by phbarrad         ###   ########.fr       */
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

char **ft_strdup_tabl(char **envp)
{
	char **hide_envp;
	int x;
	int y;
	int len;

	len = -1;
	y = -1;
	x = 0;
	while (envp[len] != NULL)
		len++;
	if (!(hide_envp = malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (envp[++y])
		hide_envp[y] = ft_strdup(envp[y]);
	hide_envp[y + 1] = NULL;
	return (hide_envp);
}

int main(int ac, char **av, char **envp)
{
	t_set *set;

	if (!(set = malloc(sizeof(t_set))))
		return (-1);
	if (ac == 3)		// for testeur
	{
		start_shell(ac, av, envp, set);
	}
	else
	{
		set->hide_envp = ft_strdup_tabl(envp);
		while (1)
		{
			disp_prompt();
			signal(SIGINT, int_handler);
			start_shell(ac, av, envp, set);
		}
	}

	free(set);
	return (0);
}
