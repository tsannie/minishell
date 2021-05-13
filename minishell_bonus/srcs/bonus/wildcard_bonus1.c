/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:24:39 by tsannie           #+#    #+#             */
/*   Updated: 2021/05/13 12:45:04 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

char	*cpy_start(int index, char *src)
{
	int		i;
	char	*res;

	res = ft_strdup("");
	i = 0;
	while (i < index)
	{
		res = add_letter(res, src[i]);
		i++;
	}
	return (res);
}

char	*spllited_wild(char *src, t_set *set, int index)
{
	char	**wild_splitted;
	char	*res;
	int		end;
	char	buff[4096 + 1];

	end = set_word(src, index, set);
	wild_splitted = ft_split(set->all_wild, '/');
	set->file = found_file(getcwd(buff, 4097), wild_splitted[0], set);
	res = cpy_start(index, src);
	res = process_file(set, res, wild_splitted, getcwd(buff, 4097));
	ft_free_dbtab(wild_splitted);
	ft_free_dbtab(set->file);
	ffree(set->all_wild);
	if (set->empty_wild == 1)
	{
		ffree(res);
		return (src);
	}
	res = ft_strjoin_free(res, &src[end]);
	ffree(src);
	return (res);
}

int		word_with_wild(char *src, int i)
{
	while (ft_istab(src[i]) != 1 && src[i] != '\'' && src[i] != '\"' && src[i])
	{
		if (src[i] == '\\')
			i += 2;
		else if (src[i] == '*')
			return (1);
		else
			i++;
	}
	return (0);
}

int		end_word(char *src, int i)
{
	while (ft_istab(src[i]) != 1 && src[i] != '\'' && src[i] != '\"' && src[i])
	{
		if (src[i] == '\\')
			i += 2;
		else
			i++;
	}
	return (i);
}

char	*wildcard(char *res, t_set *set)
{
	int		i;

	i = 0;
	while (res[i])
	{
		if (res[i] == '\\')
			i += 2;
		else if (res[i] == '\'' || res[i] == '\"')
			i = forwar_quote(res, i) + 1;
		else if (word_with_wild(res, i) == 1)
		{
			set->empty_wild = 1;
			res = spllited_wild(res, set, i);
			if (set->empty_wild == 0)
				i = 0;
			else
				i = end_word(res, i);
		}
		else
			i++;
	}
	return (res);
}
