/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_correct1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:08:32 by tsannie           #+#    #+#             */
/*   Updated: 2021/04/28 14:52:25 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

int		correct_redirecion(char *src)
{
	int		i;
	char	a;

	i = 0;
	while (src[i])
	{
		if ((src[i] == '\'' || src[i] == '\"') && antislash_pair(src, i) == 1)
			i = forwar_quote(src, i);
		else if ((src[i] == '>' || src[i] == '<')
			&& antislash_pair(src, i) == 1)
		{
			if (src[i] == '>')
				a = '>';
			else if (src[i] == '<')
				a = '<';
			while (src[i] == a)
				i++;
			while (src[i] == ' ' || src[i] == '\t')
				i++;
			if (err_code(src, i) != 0)
				return (err_code(src, i));
		}
		i++;
	}
	return (0);
}

int		err_redirection(char *src, t_set *set)
{
	int e;

	if ((e = correct_redirecion(src)) != 0)
		return (call_err(e, set));
	e = multi_redirecion(src, '>');
	if (e > 3)
		return (error_list(3, set));
	else if (e > 2)
		return (error_list(7, set));
	e = multi_redirecion(src, '<');
	if (e > 4)
		return (error_list(4, set));
	else if (e > 3)
		return (error_list(8, set));
	return (0);
}

int		between_semico(const char *str, int i)
{
	int e;

	i++;
	e = 0;
	while (str[i] != ';' && str[i])
	{
		if (ft_istab(str[i]) == 0)
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

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		else if (str[i] == '\'' || str[i] == '\"')
			i = forwar_quote((char*)str, i);
		else if (str[i] == '|')
		{
			if ((e = check_pipe(str, i)) != 0)
				return (error_list(e, set));
		}
		else if (str[i] == ';' && str[i + 1] == ';')
			return (error_list(2, set));
		else if (str[i] == ';')
		{
			if ((e = between_semico(str, i)) != 0)
				return (error_list(e, set));
		}
		i++;
	}
	return (0);
}

int		correct_cmd(char *str, t_set *set)
{
	if (first_part(str, set) == -1)
		return (-1);
	if (check_list(str, set) == -1)
		return (-1);
	if (err_redirection(str, set) == -1)
		return (-1);
	return (0);
}
