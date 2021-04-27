/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 07:41:05 by tsannie           #+#    #+#             */
/*   Updated: 2021/04/27 07:29:58 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

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
	if (is_wild(line_parce) == 1)				// after search_dolars
		line_parce = wildcard(line_parce, set);
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
