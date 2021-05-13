/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 12:43:27 by tsannie           #+#    #+#             */
/*   Updated: 2021/05/13 12:43:47 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

char	*add_allfile(char *src, char **list_to_add, t_set *set, int a)
{
	int		i;

	i = 0;
	while (list_to_add[i])
	{
		src = ft_strjoin_free(src, " ");
		if (a > 0)
		{
			src = ft_strjoin_free(src, set->file[a - 1]);
			src = ft_strjoin_free(src, "/");
		}
		src = ft_strjoin_free(src, list_to_add[i]);
		i++;
		set->empty_wild = 0;
	}
	return (src);
}

int		set_word(char *src, int i, t_set *set)
{
	set->all_wild = ft_strdup("");
	while (ft_istab(src[i]) != 1 && src[i] != '\'' && src[i] != '\"' && src[i])
	{
		if (src[i] == '\\')
			i++;
		set->all_wild = add_letter(set->all_wild, src[i]);
		i++;
	}
	return (i);
}

void	search_in_dir(t_set *set, char *part_wild, char *name_dir, char *pwd)
{
	char	*dst;

	dst = ft_strjoin(pwd, "/");
	dst = ft_strjoin_free(dst, name_dir);
	set->fnd_file = found_file(dst, part_wild, set);
	ffree(dst);
	if (set->fnd_file[0])
		ft_sort_file(set->fnd_file);
}

char	*process_file(t_set *set, char *res, char **wild_splitted, char *pwd)
{
	int		i;

	if (set->file[0])
		ft_sort_file(set->file);
	if (wild_splitted[1])
	{
		i = 0;
		while (set->file[i])
		{
			search_in_dir(set, wild_splitted[1], set->file[i], pwd);
			res = add_allfile(res, set->fnd_file, set, i + 1);
			ft_free_dbtab(set->fnd_file);
			i++;
		}
	}
	else if (set->file[0])
		res = add_allfile(res, set->file, set, 0);
	return (res);
}
