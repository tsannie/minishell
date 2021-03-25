/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:30:07 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/24 16:03:07 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char	*ft_strdupbc(const char *s1)
{
	char	*res;
	int		len;
	int		i;

	len = 0;
	while (s1[len])
		len++;
	while (s1[len] != '/' && len > 0)
		len--;
	//printf("len = [%d]\n", len);
	i = 0;
	if (!(res = malloc(sizeof(char) * (len + 2))))
		return (NULL);
	while (s1[i] && i <= len)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	//printf("res = [%s]\n", res);
	return (res);
}

int			is_dir(char *arg)
{
	int		file;

	file = open(arg, O_DIRECTORY);
	//printf("file = %d, str = %s\n", file, arg);
	if (file != -1)
	{
		close(file);
		return (1);
	}
	close(file);
	return (0);
}

int		is_dir_present(char *arg, char *cmd)
{
	DIR				*folder;
	struct dirent	*item;

	folder = opendir(arg);
	if (!folder)
		return (0);
	while ((item = readdir(folder)))
	{
		//printf("[%s][%s]\n", item->d_name, cmd);
		if (ft_strcmp(item->d_name, cmd) == 0 && is_dir(item->d_name) == 0)
		{
			closedir(folder);
			return (1);
		}
	}
	closedir(folder);
	return (0);
}

int		is_dir_presentsl(char *arg, char *cmd)
{
	DIR				*folder;
	struct dirent	*item;

	folder = opendir(arg);
	if (!folder)
		return (0);
	while ((item = readdir(folder)))
	{
		//printf("[%s] == [%s]\n", cmd, item->d_name);
		if (ft_strcmpss(cmd, item->d_name) == 0 && is_dir(item->d_name) == 0)
		{
			closedir(folder);
			return (1);
		}
	}
	closedir(folder);
	return (0);
}
