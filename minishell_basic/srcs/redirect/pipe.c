/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 09:28:39 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/29 15:11:14 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

int		is_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i += 2;
		else if (str[i] == '\'' || str[i] == '\"')
			i = forwar_quote(str, i) + 1;
		else if (str[i] == '|')
			return (1);
		else
			i++;
	}
	return (0);
}

char	*new_pipe(char *str, t_set *set)
{
	char	*tmp;
	int		len;

	len = set->p;
	while (str[set->p] && str[set->p] != '|')
	{
		if (str[set->p] == '\\')
			set->p += 2;
		else if ((str[set->p] == '\'' || str[set->p] == '\"')
			&& antislash_pair(str, set->p) == 1)
			set->p = forwar_quote(str, set->p) + 1;
		else
			set->p++;
	}
	len = (set->p - len) + 1;
	set->p++;
	if (!(tmp = malloc(sizeof(char) * len)))
		return (NULL);
	ft_strlcpy(tmp, &str[set->p - (len)], len);
	return (tmp);
}

char	**split_pipe(char *str, t_set *set)
{
	char	**res;
	char	*add_this;
	int		i;

	if (!(res = malloc(sizeof(char*) * 1)))
		return (NULL);
	res[0] = 0;
	i = 1;
	while (set->p < (int)ft_strlen(str))
	{
		add_this = new_pipe(str, set);
		res = addword(res, i, add_this);
		i++;
		free(add_this);
	}
	return (res);
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
