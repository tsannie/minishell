/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 09:28:39 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/23 13:39:08 by tsannie          ###   ########.fr       */
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
		//printf("c = {%c}\n", str[set->p]);
		if (str[set->p] == '\\')
			set->p += 2;
		else if ((str[set->p] == '\'' || str[set->p] == '\"') && antislash_pair(str, set->p) == 1)
			set->p = forwar_quote(str, set->p) + 1;
		else
			set->p++;
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
	//printf("split pipe -> ");
	//print_args(res);
	return(res);
}

int		son(int pipefd[2], int fd_in, t_set *set)
{
	dup2(fd_in, STDIN); //if there was a pipe before, connecting this command to previous one
	if (set->push[set->p + 1]) //if there is an other pipe after this command we redirect its output into the pipefd
	{
		dup2(pipefd[1], STDOUT); //otherwise this command is the last one and will print to stdout
		//printf("LEAVE\n");
	}
	ifclose(fd_in);     //now saved in STDIN
	ifclose(pipefd[0]); //son is taking the input previously save from STDIN / or a previous pipe (fd_in)
	ifclose(pipefd[1]); //now saved in STDOUT if there is a next command
	exec_cmd(set, set->push[set->p]);
	//printf("exit\n");
	exit(set->exit_val); //sets in execve_part
}

void		start_pipe(t_set *set)
{
	int			pipefd[2];
	int			fd_in; //for saving the input of next command to be executed
	int			status;
	pid_t		pid;
	int			nb_wait;

	status = 0;
	nb_wait = 0;
	pid = -1;
	fd_in = dup(STDIN);
	while (set->push[set->p])
	{
		//printf("set->push[set->p] = {%s}\n", set->push[set->p]);
		pipe(pipefd);
		pid = fork();
		//printf("set->pid\t=\t%d\n", pid);
		if (pid == 0)		//son
		{
			//printf("\t\t\tenter HERE\n");
			son(pipefd, fd_in, set);
		}
		else				//parent
		{
			ifclose(fd_in);			//we will copy pipe_intput inside
			fd_in = dup(pipefd[0]);	//saving pipe_input, will be use in the next loop
			ifclose(pipefd[0]);		//saved in fd_in
			ifclose(pipefd[1]);		//not used
			nb_wait++;
		}
		set->p++;
	}
	ifclose(fd_in); //close last save of pipefd[0]
	reset_fd(set);
	while (nb_wait-- >= 0) //waiting that all the processes launched end
		if (wait(&status) == pid)
		{
			//printf("now wait\n");
			set->exit_val = WEXITSTATUS(status);
			set->bleu = 1;
			add_exval(set);
			//printf("ret = %d\n", set->exit_val);
		}
}