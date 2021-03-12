/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 07:41:05 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/12 09:29:27 by tsannie          ###   ########.fr       */
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
	while ((ft_iswhite(src[set->y]) == 1 && quot == 0) || (src[set->y] == '\"' && src[set->y + 1] == '\"')
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
		else if (ft_iswhite(src[set->y]) != 1)
		{
			while (src[set->y] && ft_iswhite(src[set->y]) != 1 && src[set->y] != '\'' && src[set->y] != '\"')
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
		if ((ft_iswhite(src[set->y]) == 1 || !src[set->y]) && exit == 0)
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

int		multi_redirecion(char *src, t_set *set, char a)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	while (src[i])
	{
		if ((src[i] == '\'' || src[i] == '\"') && antislash_pair(src, i) == 1)
			i = forwar_quote(src, i);
		else if (src[i] == a)
		{
			while (src[i] == a)		// possible seg fault
			{
				i++;
				e++;
			}
			if (e > 2 && a == '>')
				return (e);
			if (e > 3 && a == '<')
				return (e);
			e = 0;
		}
		i++;
	}
	return (e);
}

int		correct_redirecion(char *src, t_set *set)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if ((src[i] == '\'' || src[i] == '\"') && antislash_pair(src, i) == 1)
			i = forwar_quote(src, i);
		else if (src[i] == '>' || src[i] == '<')
		{
			if (src[i] == '>')
			{
				while (src[i] == '>')
					i++;
			}
			else
			{
				while (src[i] == '<')
					i++;
			}
			while (src[i] == ' ')
				i++;
			if (src[i] == '>' && src[i + 1] == '>')
				return (1);
			if (src[i] == '<' && src[i + 1] == '<')
				return (2);
			if (src[i] == '<' && src[i + 1] == '>')
				return (3);
			if (src[i] == '>')
				return (5);
			if (src[i] == '<')
				return (6);
			if (src[i] == ';')
				return (7);
			if (!(src[i]))
				return (8);
		}
		i++;
	}
	return (0);
}

int	error_list(int a, t_set *set)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", STDERR);
	if (a == 1)
		ft_putstr_fd("`;'", STDERR);
	if (a == 2)
		ft_putstr_fd("`;;'", STDERR);
	if (a == 3)
		ft_putstr_fd("`>>'", STDERR);
	if (a == 4)
		ft_putstr_fd("`<<'", STDERR);
	if (a == 5)
		ft_putstr_fd("`<>'", STDERR);
	if (a == 7)
		ft_putstr_fd("`>'", STDERR);
	if (a == 8)
		ft_putstr_fd("`<'", STDERR);
	if (a == 9)
		ft_putstr_fd("`newline'", STDERR);
	ft_putstr_fd("\n", STDERR);
	set->exit_val = 2;
	return (-1);
}

int		err_redirection(char *src, t_set *set)
{
	int e;

	e = multi_redirecion(src, set, '>');
	if (e > 3)
		return (error_list(3, set));
	else if (e > 2)
		return (error_list(7, set));

	e = multi_redirecion(src, set, '<');
	if (e > 4)
		return (error_list(4, set));
	else if (e > 3)
		return (error_list(8, set));

	e = correct_redirecion(src, set);
	if (e == 1)
		return (error_list(3, set));
	else if (e == 2)
		return (error_list(4, set));
	else if (e == 3)
		return (error_list(5, set));
	else if (e == 5)
		return (error_list(7, set));
	else if (e == 6)
		return (error_list(8, set));
	else if (e == 7)
		return (error_list(1, set));
	else if (e == 8)
		return (error_list(9, set));
	return (0);
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

int 	first_semicon(const char *str)
{
	int	i;
	int	e;

	e = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ';')
		{
			if (str[i] == ';' && str[i + 1] == ';')
				return (2);
			if (str[i] == ';' && e == 0)
				return (1);
			else
				return (0);
		}
		if (ft_iswhite(str[i]) == 0)
			e++;
		i++;
	}
	return (0);
}

int		check_list(const char *str, t_set *set)
{
	int	i;
	int	e;

	e = first_semicon(str);
	if (e != 0)
	{
		return (error_list(e, set));
	}
	e = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ';' && str[i + 1] == ';')
			return (error_list(2, set));
		if (str[i] == ';')
		{
			i++;
			e = 0;
			while (str[i] != ';' && str[i])
			{
				if (ft_iswhite(str[i]) == 0)
					e++;
				i++;
			}
			if (e == 0 && str[i])
				return (error_list(1, set));
		}
		i++;
	}
	return (0);
}

int		correct_cmd(char *str, t_set *set)
{
	if (check_list(str, set) == -1)
		return (-1);
	if (err_redirection(str, set) == -1)
		return (-1);
	return(0);
}

void	reset_fd(t_set *set)
{
	if (set->fdout > 0)			// check fd
	{
		close(set->fdout);
		set->fdout = -1;
	}
	if (set->fdin > 0)			// check fd
	{
		close(set->fdin);
		set->fdin = -1;
	}
	dup2(set->save_stdin, STDIN);
	dup2(set->save_stdout, STDOUT);
}

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
	}
	return (0);
}

void	treat_cmd(t_set *set)
{
	char **list;
	int i;
	int e;

	i = 0;
	if (correct_cmd(set->str, set) == 0)
	{
		list = split_semicolon(set->str, set);
		while (list[i])
		{
			set->stop = 0;
			e = 0;
			set->err_quote = 0;

			if (is_pipe(list[i]) == 1)
				start_pipe(list[i], set);

			clean(list[i], set);
			if (set->stop == 0)
				start_cmd(set);
			free(set->cmd);
			while (set->arg[e])
			{
				//printf("\n\n\nset->arg[e] = %s\n\n\n", set->arg[e]);
				free(set->arg[e]);
				e++;
			}
			free(set->arg);
			reset_fd(set);
			i++;
		}
		e = 0;
		while (list[e])
		{
			free(list[e]);
			e++;
		}
		free(list);
	}
}
