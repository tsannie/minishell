/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_correct3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:21:01 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/23 16:24:10 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

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
			while (src[i] == a)
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

int		first_semicon(const char *str)
{
	int	i;
	int	e;

	e = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i += 2;
		else if (str[i] == '\'' || str[i] == '\"')
			i = forwar_quote((char*)str, i);
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

int		error_list(int a, t_set *set)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", STDERR);
	(a == 1) ? ft_putstr_fd("`;'", STDERR) : 0;
	(a == 2) ? ft_putstr_fd("`;;'", STDERR) : 0;
	(a == 3) ? ft_putstr_fd("`>>'", STDERR) : 0;
	(a == 4) ? ft_putstr_fd("`<<'", STDERR) : 0;
	(a == 5) ? ft_putstr_fd("`<>'", STDERR) : 0;
	(a == 7) ? ft_putstr_fd("`>'", STDERR) : 0;
	(a == 8) ? ft_putstr_fd("`<'", STDERR) : 0;
	(a == 9) ? ft_putstr_fd("`newline'", STDERR) : 0;
	(a == 10) ? ft_putstr_fd("`|'", STDERR) : 0;
	(a == 11) ? ft_putstr_fd("`||'", STDERR) : 0;
	ft_putstr_fd("\n", STDERR);
	set->exit_val = 258;
	set->bleu = 1;
	add_exval(set);
	return (-1);
}

int		err_code(char *src, int i, t_set *set)
{
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
	if (src[i] == '|' && src[i + 1] == '|')
		return (9);
	if (src[i] == '|')
		return (10);
	return (0);
}

int		call_err(int e, t_set *set)
{
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
		return (error_list(11, set));
	else if (e == 10)
		return (error_list(10, set));
	return (0);
}
