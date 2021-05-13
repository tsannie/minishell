/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:07:05 by phbarrad          #+#    #+#             */
/*   Updated: 2021/05/13 12:40:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

int					is_dir(char *arg)
{
	int				file;

	file = open(arg, O_DIRECTORY);
	if (file != -1)
	{
		ifclose(file);
		return (1);
	}
	ifclose(file);
	return (0);
}

int					is_dir_present(char *arg, char *cmd)
{
	DIR				*folder;
	struct dirent	*item;

	folder = opendir(arg);
	if (!folder)
		return (0);
	while ((item = readdir(folder)))
	{
		if (ft_strcmp(item->d_name, cmd) == 0 && is_dir(item->d_name) == 0)
		{
			closedir(folder);
			return (1);
		}
	}
	closedir(folder);
	return (0);
}

int					is_dir_presentsl(char *arg, char *cmd)
{
	DIR				*folder;
	struct dirent	*item;

	folder = opendir(arg);
	if (!folder)
		return (0);
	while ((item = readdir(folder)))
	{
		if (ft_strcmpss(cmd, item->d_name) == 0 && is_dir(item->d_name) == 0)
		{
			closedir(folder);
			return (1);
		}
	}
	closedir(folder);
	return (0);
}

void				rres(char **res, int word, int n, char str)
{
	if (str != '/')
	{
		res[word][n] = '/';
		res[word][n + 1] = '\0';
	}
	else
		res[word][n] = '\0';
}

char				*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;
	int		globalsize;
	int		i;
	int		e;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (NULL);
	globalsize = ft_strlen(s1) + ft_strlen(s2);
	if (!(res = malloc(sizeof(char) * globalsize + 1)))
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	free(s1);
	s1 = NULL;
	e = -1;
	while (s2[++e])
		res[i + e] = s2[e];
	res[globalsize] = '\0';
	return (res);
}
