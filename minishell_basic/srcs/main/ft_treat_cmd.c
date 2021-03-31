/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 07:41:05 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/29 15:11:14 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

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

char	*add_letter(char *str, char a)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(str) + 2;
	if (!(res = malloc(sizeof(char) * len)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = a;
	res[len - 1] = '\0';
	if (str)
		free(str);
	return (res);
}

void	search_cmd(const char *src, t_set *set)
{
	int		exit;

	set->y = 0;
	set->word_tmp = ft_strdup("");
	while (ft_istab(src[set->y]) == 1 && src[set->y])
		set->y++;
	exit = 0;
	while (exit == 0)
	{
		if (src[set->y] == '\'')
			exit = search_quotes(src, set, '\'');
		else if (src[set->y] == '\"')
			exit = search_quotes(src, set, '\"');
		else if (ft_istab(src[set->y]) != 1)
			search_basic(src, set);
		if ((ft_istab(src[set->y]) == 1 || !src[set->y]) && exit == 0)
			exit = 1;
	}
	if (exit == -1)
		set->err_quote = 1;
	set->cmd = ft_strdup(set->word_tmp);
	ffree(set->word_tmp);
}

int		forwar_quote(char *src, int i)
{
	if (src[i] == '\'')
	{
		i++;
		while (src[i] && src[i] != '\'')
			i++;
	}
	else if (src[i] == '\"')
	{
		i++;
		while (src[i] && src[i] != '\"')
		{
			if (src[i] == '\\')
				i = i + 2;
			else
				i++;
		}
	}
	return (i);
}

int		clean(char *src, t_set *set)
{
	char	*cpy;
	char	*line_parce;

	cpy = redirection(src, set);
	line_parce = search_dolars(cpy, set);
	free(cpy);
	search_cmd(line_parce, set);
	search_arg(line_parce, set);
	free(line_parce);
	return (0);
}

void	exec_cmd(t_set *set, char *cmd)
{
	set->stop = 0;
	set->err_quote = 0;
	clean(cmd, set);
	if (set->stop == 0)
		start_cmd(set);
	free(set->cmd);
	ft_free_dbtab(set->arg);
}

void	treat_cmd(t_set *set)
{
	int		i;

	i = 0;
	if (correct_cmd(set->str, set) == 0)
	{
		set->list = split_semicolon(set->str, set);
		while (set->list[i])
		{
			set->p = 0;
			set->simple = (is_pipe(set->list[i]) == 0) ? 1 : 0;
			set->push = split_pipe(set->list[i], set);
			set->p = 0;
			if (set->simple == 1)
				exec_cmd(set, set->push[0]);
			else
				start_pipe(set);
			reset_fd(set);
			ft_free_dbtab(set->push);
			i++;
		}
		ft_free_dbtab(set->list);
	}
}
