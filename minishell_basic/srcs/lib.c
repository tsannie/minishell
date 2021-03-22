/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:30:07 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/22 13:38:06 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char	*ft_strduplen(const char *s1, int len)
{
	char	*res;
	size_t	i;

	i = 0;
	if (!(res = malloc(sizeof(char) * (len))))
		return (NULL);
	while (s1[i] && i < len)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
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
	int				valid;

	valid = 0;
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