/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 09:28:39 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/18 12:43:35 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int		is_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		//printf("res[i] = {%c} | res = {%s} | i = %d\n", res[i], res, i);
		if ((str[i] == '\'' || str[i] == '\"') && antislash_pair(str, i) == 1)
			i = forwar_quote(str, i);
		else if (str[i] == '|' && antislash_pair(str, i) == 1)				//	warn backslash
		{

			return (1);
		}
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
		if ((str[set->p] == '\'' || str[set->p] == '\"') && antislash_pair(str, set->p) == 1)
			set->p = forwar_quote(str, set->p);
		else
			set->p++;
		if (str[set->p] == '|' && antislash_pair(str, set->p) == 0)
			set->p += 2;
	}
	len = (set->p - len) + 1;
	set->p++;
	//printf("i = %d\n", i);
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
	while (set->p < ft_strlen(str))
	{
		add_this = new_pipe(str, set);
		res = addword(res, i, set, add_this);
		i++;
		free(add_this);
	}
	//print_args(res);
	return(res);
}

int		pipe_exec_son(t_set *set, int fdpipe[2], int fd_in)
{
	dup2(fd_in, STDIN_FILENO); //if there was a pipe before, connecting this command to previous one
	if (set->push[set->p + 1]) //if there is an other pipe after this command we redirect its output into the fdpipe
	{
		dup2(fdpipe[1], STDOUT_FILENO); //otherwise this command is the last one and will print to stdout
		//printf("LEAVE\n");
	}
	close(fd_in);     //now saved in STDIN
	close(fdpipe[0]); //son is taking the input previously save from STDIN / or a previous pipe (fd_in)
	close(fdpipe[1]); //now saved in STDOUT if there is a next command
	exec_cmd(set, set->push[set->p]);
	//printf("exit\n");
	exit(set->ret_value); //sets in execve_part
}

int		start_pipe(t_set *set)
{
	int			fdpipe[2];
	int			fd_in; //for saving the input of next command to be executed
	int			status;
	pid_t		pid;
	int			nb_wait;

	status = 0;
	nb_wait = 0;
	pid = -1;
	fd_in = dup(STDIN_FILENO);
	while (set->push[set->p] && pid != 0)
	{
		//printf("set->push[set->p] = {%s}\n", set->push[set->p]);
		if (pipe(fdpipe) == -1)
			return (set->ret_value = 1);
		pid = fork();
		//printf("set->pid\t=\t%d\n", pid);
		if (pid == 0)		//son
		{
			//printf("\t\t\tenter HERE\n");
			pipe_exec_son(set, fdpipe, fd_in);
		}
		else				//parent
		{
			close(fd_in);			//we will copy pipe_intput inside
			fd_in = dup(fdpipe[0]);	//saving pipe_input, will be use in the next loop
			close(fdpipe[0]);		//saved in fd_in
			close(fdpipe[1]);		//not used
			nb_wait++;
		}
		set->p++;
	}
	close(fd_in); //close last save of fdpipe[0]
	reset_fd(set);
	while (nb_wait-- >= 0) //waiting that all the processes launched end
		if (wait(&status) == pid)
		{
			//printf("now wait\n");
			set->ret_value = WEXITSTATUS(status);
		}

	return (0);
}