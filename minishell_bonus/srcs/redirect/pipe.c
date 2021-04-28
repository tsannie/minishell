/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 09:28:39 by tsannie           #+#    #+#             */
/*   Updated: 2021/04/28 14:52:25 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void	ifclose(int fd)
{
	if (fd > 0)
		close(fd);
}

void	reset_fd(t_set *set)
{
	ifclose(set->fdout);
	ifclose(set->fdin);
	set->fdin = -1;
	set->fdout = -1;
	dup2(set->save_stdin, STDIN);
	dup2(set->save_stdout, STDOUT);
}

int		son(int pipefd[2], int fd_in, t_set *set)
{
	dup2(fd_in, STDIN);
	if (set->push[set->p + 1])
		dup2(pipefd[1], STDOUT);
	ifclose(fd_in);
	ifclose(pipefd[0]);
	ifclose(pipefd[1]);
	exec_cmd(set, set->push[set->p]);
	exit(set->exit_val);
}

void	wait_end(int fd_in, pid_t pid, t_set *set)
{
	int			status;

	ifclose(fd_in);
	reset_fd(set);
	while (set->wait-- >= 0)
	{
		if (wait(&status) == pid)
		{
			set->exit_val = WEXITSTATUS(status);
			set->bleu = 1;
			add_exval(set);
		}
	}
}

void	start_pipe(t_set *set)
{
	int			pipefd[2];
	int			fd_in;
	pid_t		pid;

	set->wait = 0;
	pid = -1;
	fd_in = dup(STDIN);
	while (set->push[set->p])
	{
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
			son(pipefd, fd_in, set);
		else
		{
			ifclose(fd_in);
			fd_in = dup(pipefd[0]);
			ifclose(pipefd[0]);
			ifclose(pipefd[1]);
			set->wait++;
		}
		set->p++;
	}
	wait_end(fd_in, pid, set);
}
