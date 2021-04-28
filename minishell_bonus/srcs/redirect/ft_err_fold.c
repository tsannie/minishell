/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_fold.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 10:49:31 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/28 14:52:25 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

int		eexxfold(char *tmp3, t_set *set, int i)
{
	ffree(tmp3);
	if (ft_strlen(set->argss[i]) > 0)
	{
		if (i == 0 && is_dir(set->argss[i]) == 0 &&
		set->argss[i][ft_strlen(set->argss[i]) - 1] == '/')
		{
			ft_free_dbtab(set->argss);
			return (1);
		}
	}
	ft_free_dbtab(set->argss);
	return (0);
}

int		exxval(char *tmp, char *tmp2, char *tmp3, t_set *set)
{
	ffree(tmp);
	ffree(tmp2);
	ffree(tmp3);
	ft_free_dbtab(set->argss);
	set->exit_val = 4;
	return (4);
}

int		intit(int i, char *tmp, char *tmp2)
{
	ffree(tmp);
	ffree(tmp2);
	return (i + 1);
}

void	err_exist(t_set *set, char *namefile)
{
	if (set->fdout == -1)
	{
		if (set->not_exist == 1)
			set->not_exist = 3;
		else if (set->not_exist == 4)
			set->not_exist = 1;
		else
			set->not_exist = 2;
	}
	if (set->not_exist == 0)
	{
		free(namefile);
		dup2(set->fdout, STDOUT);
	}
	else
		set->namefile = namefile;
}

int		err_folder(t_set *set, char *namefile, int i)
{
	char *tmp;
	char *tmp2;
	char *tmp3;

	tmp3 = ft_strdup("");
	tmp = ft_strdup("");
	tmp2 = NULL;
	set->argss = ft_split(namefile, '/');
	while (set->argss[i + 1] && set->not_exist == 0)
	{
		if (i > 0)
			tmp = ft_strjoin(tmp3, "/");
		ffree(tmp3);
		tmp2 = ft_strjoin(tmp, set->argss[i]);
		tmp3 = ft_strdup(tmp2);
		if (is_dir(tmp2) == 0)
		{
			if (is_dir_present(tmp, set->argss[i]) == 0)
				return (exxval(tmp, tmp2, tmp3, set));
			set->exit_val = exxval(tmp, tmp2, tmp3, set);
			return (1);
		}
		i = intit(i, tmp, tmp2);
	}
	return (eexxfold(tmp3, set, i));
}
