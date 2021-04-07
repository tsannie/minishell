/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:52:30 by tsannie           #+#    #+#             */
/*   Updated: 2021/04/07 10:32:15 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void	create_file(char *namefile, t_set *set, int a)
{
	int i;

	i = 0;
	ifclose(set->fdout);
	set->not_exist = err_folder(set, namefile, i);
	if (a == 1)
		set->fdout = open(namefile, O_CREAT | O_WRONLY | O_TRUNC, 00700);
	else if (a == 2)
		set->fdout = open(namefile, O_CREAT | O_WRONLY | O_APPEND, 00700);
	err_exist(set, namefile);
}

void	change_stdin(char *namefile, t_set *set)
{
	ifclose(set->fdin);
	if ((set->fdin = open(namefile, O_RDONLY, 00700)) == -1)
		set->not_exist = 1;
	if (set->not_exist == 0)
	{
		free(namefile);
		dup2(set->fdin, STDIN);
	}
	else
		set->namefile = namefile;
}

char	*simple_redirect(char *res, int *i, t_set *set)
{
	char	*namefile;
	char	a;

	a = (res[*(i)] == '>') ? '>' : '<';
	namefile = get_namefile(res, set, *(i));
	if (!namefile[0])
		set->amb = 1;
	if (set->amb == 1 && namefile)
		free(namefile);
	if (set->amb == 0 && set->err_quote == 0)
	{
		res = get_newcmd(res, set, *(i));
		if (a == '>')
			create_file(namefile, set, 1);
		else
			change_stdin(namefile, set);
	}
	*(i) = -1;
	return (res);
}

char	*double_redirect(char *res, int *i, t_set *set)
{
	char	*namefile;

	namefile = get_namefile(res, set, *(i) + 1);
	if (!namefile[0])
		set->amb = 1;
	if (set->amb == 1 && namefile)
		free(namefile);
	if (set->amb == 0 && set->err_quote == 0)
	{
		res = get_newcmd(res, set, *(i));
		create_file(namefile, set, 2);
	}
	*(i) = -1;
	return (res);
}

char	*redirection(char *src, t_set *set)
{
	int		i;
	char	*res;

	set->dol_amb = ft_strdup("");
	res = ft_strdup(src);
	i = 0;
	set->not_exist = 0;
	set->amb = 0;
	while (res[i] && set->stop == 0)
	{
		if (antislash_pair(res, i) == 1)
		{
			if ((res[i] == '\'' || res[i] == '\"'))
				i = forwar_quote(res, i);
			else if (res[i] == '>' && res[i + 1] == '>')
				res = double_redirect(res, &i, set);
			else if ((res[i] == '>' || res[i] == '<'))
				res = simple_redirect(res, &i, set);
		}
		check_err_and_incr(set, &i);
	}
	ffree(set->dol_amb);
	add_exval(set);
	return (res);
}
