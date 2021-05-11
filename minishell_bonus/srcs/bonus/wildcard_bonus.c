/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:24:39 by tsannie           #+#    #+#             */
/*   Updated: 2021/05/11 12:58:29 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void		ft_sort_file(char **dbtab)
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
