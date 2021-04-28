/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:24:39 by tsannie           #+#    #+#             */
/*   Updated: 2021/04/28 14:52:28 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void	print_args(char **str)			// TO DELETE
{
	int		i;

	i = 0;
	if (!str[0])
	{
		printf("NO ARGS\n");
	}
	else
	{
		printf("args_stock : \n");
		while (str[i])
		{
			printf("- Argument %d\t:\t|%s|\n", i, str[i]);
			i++;
		}
	}
}

void		ft_sort_file(t_set *set)
{
	int		i;
	char	*temp;

	i = 0;
	while (set->file[i + 1] != NULL)
	{
		if (ft_strcmp(set->file[i], set->file[i + 1]) > 0)
		{
			temp = set->file[i];
			set->file[i] = set->file[i + 1];
			set->file[i + 1] = temp;
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

// test *c* for first
int		correct_patern(char *file, t_set *set)
{
	int	i;
	int com;

	//printf("file . (%s)\n", file);
	if (set->wild[0] != '.' && file[0] == '.')
		return (0);
	i = 0;
	com = 0;
	while (set->wild[com] != '*' && set->wild[com])
	{
		if (file[i] != set->wild[com])
			return (0);
		i++;
		com++;
	}
	//printf("Step 1\n com = %d\ni = %d\n", com, i);
	while (file[i])
	{
		if (set->wild[com] == '*')
			com++;
		else if (file[i] == set->wild[com])
		{
			com++;
			i++;
		}
		else
			i++;
	}
	while (set->wild[com] == '*')
		com++;
	//printf("Step 2\n com = %d\ni = %d\n", com, i);
	if ((int)ft_strlen(set->wild) != com)
		return (0);
	com--;
	i--;
	while (set->wild[com] != '*')
	{
		if (file[i] != set->wild[com])
			return (0);
		i--;
		com--;
	}

	return (1);
}

void	cpy_filename(t_set *set)
{
	DIR				*folder;
	struct dirent	*item;
	int				word;
	char	buff[4096 + 1];

	if (!(set->file = malloc(sizeof(char*) * 1)))
		return ;
	set->file[0] = 0;
	word = 0;
	folder = opendir(getcwd(buff, 4097));
	while ((item = readdir(folder)))
	{
		if (correct_patern(item->d_name, set) == 1)
		{
			word++;
			set->file = addword(set->file, word, item->d_name);
		}
	}
	closedir(folder);
}

char	*add_allfile(char *src, t_set *set)
{
	int		i;

	i = 0;
	while (set->file[i])
	{
		src = ft_strjoin_free(src, " ");
		src = ft_strjoin_free(src, set->file[i]);
		i++;
	}
	return (src);
}

int		set_word(char *src, int i, t_set *set)
{
	set->wild = ft_strdup("");
	while (ft_istab(src[i]) != 1 && src[i] != '\'' && src[i] != '\"' && src[i])
	{
		if (src[i] == '\\')
			i++;
		set->wild = add_letter(set->wild, src[i]);
		i++;
	}
	return (i);
}

char	*place_file(char *src, t_set *set, int index)
{
	char	*res;
	int		i;
	int		end;

	res = ft_strdup("");
	end = set_word(src, index, set);
	//printf("word = [%s]\n", set->wild);
	i = 0;
	while (i < index)
	{
		res = add_letter(res, src[i]);
		i++;
	}
	//printf("res = {%s}\n", res);

	//printf("CRASH\n");
	cpy_filename(set);
	if (!set->file[0])
	{
		ft_free_dbtab(set->file);
		ffree(res);
		ffree(set->wild);
		set->empty_wild = 1;
		return (src);
	}
	//printf("CRASH1\n");
	//print_args(set->file);
	ft_sort_file(set);
	//printf("CRASH2\n");

	//print_args(set->file);

	res = add_allfile(res, set);
	//printf("res = {%s}\n", res);

	res = ft_strjoin_free(res, &src[end]);
	//printf("res = {%s}\n", res);
	ft_free_dbtab(set->file);
	ffree(set->wild);
	return (res);
}

int		not_empty(void)
{
	DIR				*folder;
	struct dirent	*item;
	int 			cpt;
	char	buff[4096 + 1];

	cpt = 0;
	//printf("pwd = {%s}\n", getcwd(buff, 4097));
	folder = opendir(getcwd(buff, 4097));
	if (!folder)
		return (-1);
	while ((item = readdir(folder)))
	{
		//printf("{%s}\n", item->d_name);
		if (item->d_name[0] != '.')
			cpt++;
	}
	closedir(folder);
	return ((cpt == 0) ? 0 : 1);
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

char	*wildcard(char *src, t_set *set)	// redirection '*'
{
	char	*res;
	int		i;

	res = ft_strdup(src);
	i = 0;
	while (res[i])
	{
		if (res[i] == '\\')
			i += 2;
		else if (res[i] == '\'' || res[i] == '\"')
			i = forwar_quote(res, i) + 1;
		else if (word_with_wild(res, i))
		{
			if (not_empty() == 1)
			{
				set->empty_wild = 0;
				res = place_file(res, set, i);
				if (set->empty_wild == 0)
					i = 0;
				else
					i = end_word(res, i);
			}
			else
			{
				//printf("ENTERRR\n");
				i++;
			}
		}
		else
			i++;
	}
	free(src);
	return (res);
}
