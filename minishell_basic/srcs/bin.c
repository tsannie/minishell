/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 12:18:28 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/03 14:46:55 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char	*ft_strdup_m(char *str)
{
	char *cmd;
	int len;
	int x;

	x = -1;
	len = 0;
	while (str[len] && ft_strncmp(str + len, "/bin/", 5) != 0)
		len++;
	if (len == ft_strlen(str))
		return (NULL);
	len += 5;
	if (!(cmd = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (++x < len)
		cmd[x] = str[x];
	cmd[x + 1] = '\0';
	return (cmd);
}

char	*ft_strdup_p(char *str)
{
	char *cmd;
	int len;
	int x;
	int e;

	e = 0;
	x = -1;
	len = 0;
	while (str[len] && ft_strncmp(str + len, "/bin/", 5) != 0)
	{
		//printf("[%s][/bin/][%d]\n", str+len , ft_strncmp(str + len, "/bin/", 5));
		len++;
	}
	printf("\n\n[%d][%d]\n", len , ft_strlen(str));
	if (len == ft_strlen(str))
		return (NULL);
	len += 5;
	while (str[len + e] && str[len + e] != ' ')
		e++;
	if (!(cmd = malloc(sizeof(char) * (e + 1))))
		return (NULL);
	while (++x < e)
		cmd[x] = str[x + len];
	cmd[x + 1] = '\0';
	return (cmd);
}

char 	*get_path(t_set *set)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;
	char			*cmd_m;
	char 			*cmd_p;
	int 			valid;

	valid = 0;
	cmd_m = ft_strdup_m(set->cmd);
	cmd_p = ft_strdup_p(set->cmd);
	//printf("\n\n[%s]--[%s]\n\n\n", cmd_m, cmd_p);
	if (cmd_p == NULL || cmd_m == NULL)
		return (NULL);
	folder = opendir(cmd_m);
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)))
	{
		if (ft_strcmp(item->d_name, cmd_p) == 0)
			valid = 1;
	}
	closedir(folder);
	if (valid == 1)
		return (ft_strjoin(cmd_m, cmd_p));
	return (NULL);
}

int		bash_cmd(t_set *set)
{
	char *path;
	int x = -1;

	path = get_path(set);
	//printf("{%s}{%s}\n", path, set->str);
	while (set->arg[++x])
		//printf("arg = [%s]\n", set->arg[x]);
 	if (path != NULL)
	{
		execve(path, set->arg, set->envp);
	}
	return (1);
}