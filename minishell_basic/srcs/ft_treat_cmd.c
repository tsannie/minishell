/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 07:41:05 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/23 15:13:00 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minish.h"

char	*add_letter(char *str, char a)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(str) + 2;
	if (!(res = malloc(sizeof(char) * len)))
		return NULL;
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = a;
	res[len - 1] = '\0';	//pas sur du -1 flm de reflaichir
	if (str)
		free(str);
	return (res);
}

char	*search_cmd(const char *src, t_set *set)
{
	int		quot;
	int		exit;
	char	*res;

	set->y = 0;
	quot = 0;
	set->word_tmp = ft_strdup("");
	while ((ft_istab(src[set->y]) == 1 && quot == 0) || (src[set->y] == '\"' && src[set->y + 1] == '\"')
		|| (src[set->y] == '\'' && src[set->y + 1] == '\''))
	{
		if ((src[set->y] == '\"' && src[set->y + 1] == '\"') || (src[set->y] == '\'' && src[set->y + 1] == '\''))
		{
			quot = 1;
			set->y++;
		}
		set->y++;
	}
	//printf("white src[y] = |%c|\n",src[set->y]);
	exit = 0;
	while (exit == 0)
	{
		if (src[set->y] == '\'')
			exit = search_quotes(src, set, '\'');
		else if (src[set->y] == '\"')
			exit = search_quotes(src, set, '\"');
		else if (ft_istab(src[set->y]) != 1)
		{
			while (src[set->y] && ft_istab(src[set->y]) != 1 && src[set->y] != '\'' && src[set->y] != '\"')
			{
				if ((src[set->y] == '\\' && src[set->y + 1]))
				{
					set->word_tmp = add_letter(set->word_tmp, src[set->y + 1]);
					set->y = set->y + 2;
				}
				else
				{
					set->word_tmp = add_letter(set->word_tmp, src[set->y]);
					set->y++;
				}
			}
		}
		if ((ft_istab(src[set->y]) == 1 || !src[set->y]) && exit == 0)
			exit = 1;
	}
	if (exit == -1)
		set->err_quote = 1;
	/* TODO if exit == -1 = {problème de quote} */
	//printf("cmd  = |%s|\nexit = %d\n", set->word_tmp, exit);
	res = ft_strdup(set->word_tmp);
	free(set->word_tmp);
	return (res);
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
			//printf("src[i] = {%c}\n", src[i]);
			if (src[i] == '\\')
				i = i + 2;
			else
				i++;
		}
	}
	return (i);
}

void ifclose(int fd)
{
	if (fd > 0)
		close(fd);
}

void	reset_fd(t_set *set)
{
	ifclose(set->fdout);
	ifclose(set->fdin);
	ifclose(set->pipein);
	ifclose(set->pipeout);
	set->fdin = -1;
	set->fdout = -1;
	set->pipein = -1;
	set->pipeout = -1;
	dup2(set->save_stdin, STDIN);
	dup2(set->save_stdout, STDOUT);
}

int		clean(char *src, t_set *set)
{
	char	*cpy;

	cpy = redirection(src, set);
	//printf("cpy_redirection = |%s|\n", cpy);
	cpy = search_dolars(cpy, set); // attention pas oublier de free cpy dans crt file
	//printf("cpy_dolars = |%s|\n", cpy);
	//printf("\n\n\n\n-------------------------------------------\nStart to clean cmd : |%s|\n", src);
	set->cmd = search_cmd(cpy, set);
	//printf("set-cmd = {%s}\nsrc = {%s}\n", set->cmd, src);
	set->arg = search_arg(cpy, set);

	return (0);
}

void	exec_cmd(t_set *set, char *cmd)
{
	//ft_putstr_fd("enter\n\n",1);
	set->stop = 0;
	set->err_quote = 0;
	clean(cmd, set);
	if (set->stop == 0)
		start_cmd(set);
}

void	treat_cmd(t_set *set)
{
	char **list;
	int i;
	int	status;

	i = 0;
	if (correct_cmd(set->str, set) == 0)
	{
		list = split_semicolon(set->str, set);
		//print_args(list);
		while (list[i])
		{
			set->p = 0;
			set->simple = (is_pipe(list[i]) == 0) ? 1 : 0;
			//printf("simple = %d\n", set->simple);
			set->push = split_pipe(list[i], set);
			set->p = 0;

			if (set->simple == 1)
			{
				exec_cmd(set, set->push[0]);
			}
			else
			{
				start_pipe(set);
			}
			//printf("list_before = {%s}\n", list[i]);
			//printf("list_after = {%s}\n", list[i]);
			//printf("set->simple = %d\n", set->simple);

			reset_fd(set);
			ft_free_dbtab(set->push);
			i++;
		}
		ft_free_dbtab(list);
	}
}
