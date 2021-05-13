/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 12:39:07 by tsannie           #+#    #+#             */
/*   Updated: 2021/05/13 13:43:08 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void	ft_sort_file(char **dbtab)
{
	int		i;
	char	*temp;

	i = 0;
	while (dbtab[i + 1] != NULL)
	{
		if (ft_strcmp(dbtab[i], dbtab[i + 1]) > 0)
		{
			temp = dbtab[i];
			dbtab[i] = dbtab[i + 1];
			dbtab[i + 1] = temp;
			i = -1;
		}
		i++;
	}
}

int		is_wild(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i += 2;
		else if (str[i] == '\'' || str[i] == '\"')
			i = forwar_quote(str, i) + 1;
		else if (str[i] == '*')
			return (1);
		else
			i++;
	}
	return (0);
}

int		first_part_patern(int i, char *file, char *wild, t_set *set)
{
	set->com_w = 0;
	while (wild[set->com_w] != '*' && wild[set->com_w])
	{
		if (file[i] != wild[set->com_w])
			return (0);
		i++;
		set->com_w++;
	}
	while (file[i])
	{
		if (wild[set->com_w] == '*')
			set->com_w++;
		else if (file[i] == wild[set->com_w])
		{
			set->com_w++;
			i++;
		}
		else
			i++;
	}
	return (i);
}

int		correct_patern(char *file, char *wild, t_set *set)
{
	int		i;

	if (wild[0] != '.' && file[0] == '.')
		return (0);
	if (ft_streql(file, wild) == 1)
		return (1);
	i = first_part_patern(0, file, wild, set);
	while (wild[set->com_w] == '*')
		set->com_w++;
	if ((int)ft_strlen(wild) != set->com_w)
		return (0);
	set->com_w--;
	i--;
	while (wild[set->com_w] != '*')
	{
		if (file[i] != wild[set->com_w])
			return (0);
		i--;
		set->com_w--;
	}
	return (1);
}

char	**found_file(char *dst, char *wild, t_set *set)
{
	DIR				*folder;
	struct dirent	*item;
	int				word;
	char			**res;

	if (!(res = malloc(sizeof(char*) * 1)))
		return (NULL);
	res[0] = 0;
	word = 0;
	if ((folder = opendir(dst)) == NULL)
		return (res);
	while ((item = readdir(folder)))
	{
		if (correct_patern(item->d_name, wild, set) == 1)
		{
			word++;
			res = addword(res, word, item->d_name);
		}
	}
	closedir(folder);
	return (res);
}
