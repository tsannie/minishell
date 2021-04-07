/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:24:39 by tsannie           #+#    #+#             */
/*   Updated: 2021/04/07 17:00:36 by tsannie          ###   ########.fr       */
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

void	cpy_filename(t_set *set)
{
	DIR				*folder;
	struct dirent	*item;
	int				word;
	char	buff[4096 + 1];

	word = 0;
	folder = opendir(getcwd(buff, 4097));
	while ((item = readdir(folder)))
	{
		if (item->d_name[0] != '.')
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

char	*place_file(char *src, t_set *set, int index)
{
	char	*res;
	int		i;

	if (!(set->file = malloc(sizeof(char*) * 1)))
		return (NULL);
	set->file[0] = 0;
	res = ft_strdup("");
	i = 0;
	while (i < index)
	{
		res = add_letter(res, src[i]);
		i++;
	}
	//printf("res = {%s}\n", res);
	cpy_filename(set);
	ft_sort_file(set);

	//print_args(set->file);

	res = add_allfile(res, set);
	//printf("res = {%s}\n", res);

	res = ft_strjoin_free(res, &src[i + 1]);
	//printf("res = {%s}\n", res);
	ft_free_dbtab(set->file);
	return (res);
}

int		not_empty(t_set *set)
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
		else if (res[i] == '*')
		{
			if (not_empty(set) == 1)
			{
				res = place_file(res, set, i);
				i = 0;
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
