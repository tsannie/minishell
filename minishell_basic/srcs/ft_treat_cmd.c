/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 07:41:05 by tsannie           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/03/19 09:19:50 by phbarrad         ###   ########.fr       */
=======
/*   Updated: 2021/03/19 12:37:13 by tsannie          ###   ########.fr       */
>>>>>>> f0cae79297566dc47da7787487a0674c8c68f116
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
		else if (src[i] == a && antislash_pair(src, i) == 1)
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
		else if ((src[i] == '>' || src[i] == '<') && antislash_pair(src, i) == 1)
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
			while (src[i] == ' ' || src[i] == '\t')
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
			if (src[i] == '|')
				return (9);
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
		ft_putstr_fd("`<>'", STDERR);			// ptite verif quand mem
	if (a == 7)
		ft_putstr_fd("`>'", STDERR);
	if (a == 8)
		ft_putstr_fd("`<'", STDERR);
	if (a == 9)
		ft_putstr_fd("`newline'", STDERR);
	if (a == 10)
		ft_putstr_fd("`|'", STDERR);
	if (a == 11)
		ft_putstr_fd("`||'", STDERR);
	ft_putstr_fd("\n", STDERR);
	set->exit_val = 2;
	return (-1);
}

int		err_redirection(char *src, t_set *set)
{
	int e;

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
	else if (e == 9)
		return (error_list(10, set));

	//printf("correct_redirection\n\n");

	e = multi_redirecion(src, set, '>');
	if (e > 3)
		return (error_list(3, set));
	else if (e > 2)
	{
		return (error_list(7, set));
	}

	e = multi_redirecion(src, set, '<');
	if (e > 4)
		return (error_list(4, set));
	else if (e > 3)
		return (error_list(8, set));

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
		if (str[i] == '\\')
			i += 2;
		else if (str[i] == ';')
		{
			if (str[i] == ';' && str[i + 1] == ';')
				return (2);
			if (str[i] == ';' && e == 0)
				return (1);
			else
				return (0);
		}
		else if (ft_istab(str[i]) == 0)
			e++;
		i++;
	}
	return (0);
}

int		first_pipe(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' && str[i])
		i++;
	if (str[i] == '|' && str[i + 1] == '|')
		return (11);

	if (str[i] == '|')
		return (10);
	return (0);
}

int		before_pipe(const char *str , int i)
{
	int		e;

	e = i;
	e--;
	while (str[e] == ' ' && e >= 0)
		e--;
	//printf("str[e] = %c\ne = %d\n", str[e], e);
	if (str[e] == ';' && str[i + 1] == '|')
		return (11);
	if (str[e] == ';')
		return (10);
	return (0);
}

int		after_pipe(const char *str , int i)
{
	int		e;

	e = i;
	while (str[e] == '|')
		e++;
	while (str[e] == ' ' && str[e])
		e++;
	if (str[e] == ';' && str[e + 1] == ';')
		return (2);
	if (str[e] == ';')
		return (1);
	if ((!str[e] || str[e] == '|') && str[i + 1] == '|')
		return (11);
	if (!str[e] || str[e] == '|')
		return (10);
	return (0);
}

int		nb_pipe(const char *str , int i)
{
	int	nb;

	nb = 0;
	while (str[i] == '|' && str[i])
	{
		i++;
		nb++;
	}
	if (nb >= 4)
		return (11);
	if (nb >= 2)
		return (10);
	return (0);
}

int		check_pipe(const char *str, int i)
{
	int e;


	if ((e = before_pipe(str , i)) != 0)
	{
		//printf("problem before e = %d\n",e);
		return (e);
	}
	if ((e = nb_pipe(str , i)) != 0)
	{
		//printf("problem nbpipe = %d\n",e);
		return (e);
	}
	if ((e = after_pipe(str , i)) != 0)
	{
		//printf("problem after = %d\n",e);
		return (e);
	}
	return (0);
}

int		between_semico(const char *str, int i)
{
	int e;

	i++;
	e = 0;
	while (str[i] != ';' && str[i])
	{
		if (str[i] == ' ' == 0)
			e++;
		i++;
	}
	if (e == 0 && str[i])
		return (1);
	return (0);
}

int		check_list(const char *str, t_set *set)
{
	int	i;
	int	e;
	int cpy;

	if ((e = first_pipe(str)) != 0)
		return (error_list(e, set));

	if ((e = first_semicon(str)) != 0)
		return (error_list(e, set));
	e = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i+= 2;
		else if (str[i] == '|')
		{
			//printf("ENTER\n");
			if ((e = check_pipe(str, i)) != 0)
				return (error_list(e, set));
			//printf("SORTIE\n");
		}
		else if (str[i] == ';' && str[i + 1] == ';')
		{
			return (error_list(2, set));
		}
		else if (str[i] == ';')
		{
			if ((e = between_semico(str, i)) != 0)
				return (error_list(e, set));
		}
		i++;
	}
	return (0);
}

int		correct_cmd(char *str, t_set *set)			// check all antislash
{
	if (check_list(str, set) == -1)
		return (-1);
	if (err_redirection(str, set) == -1)
		return (-1);
	return(0);
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
