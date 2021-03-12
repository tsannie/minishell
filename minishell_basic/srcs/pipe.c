/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 09:28:39 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/12 13:01:17 by tsannie          ###   ########.fr       */
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
		if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

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

char	*nextcmd(char *str, t_set *set)
{
	char	*res;
	int		len;

	len = set->p;
	while (str[set->p] && str[set->p] != '|')
	{
		if ((str[set->p] == '\'' || str[set->p] == '\"') && antislash_pair(str, set->p) == 1)
			set->p = forwar_quote(str, set->p);
		else
			set->p++;
	}
	len = (set->p - len) + 1;
	set->p++;
	//printf("set->p = %d\n", set->p);
	if (!(res = malloc(sizeof(char) * len)))
		return (NULL);
	ft_strlcpy(res, &str[set->p - (len)], len);
	//printf("str = {%s} | push = {%s} | p = %d\n\n", &str[set->p], res, set->p);
	if (!(str[set->p]))
		set->p = -1;

	return(res);
}

char	*start_pipe(char *str, t_set *set)
{
	char	*push;

	if (is_pipe(str) == 1)
	{
		push = nextcmd(str, set);
		//printf("str = {%s} | push = {%s} | p = %d\n\n", &str[set->p], push, set->p);
		//change_in_out;
	}
	else
		push = ft_strdup(str);

	return (push);
}