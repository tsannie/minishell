/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:07:05 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/07 10:32:15 by tsannie          ###   ########.fr       */
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
