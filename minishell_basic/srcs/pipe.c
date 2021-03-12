/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 09:28:39 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/12 09:29:50 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

/*	pid_t	pid;
	int		pipefd[2];

	printf("Salut\n");
	pipe(pipefd);
	pid = fork();
	printf("pip = %d\n", pid);
	if (pid == 0)
	{
		ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		set->pipein = pipefd[0];
		set->pid = -1;
		return (2);
	}
	else
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		set->pipeout = pipefd[1];
		set->pid = pid;
		return (1);
	}*/

int		start_pipe(t_set *set)
{

}