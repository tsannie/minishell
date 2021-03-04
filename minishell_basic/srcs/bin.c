/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 12:18:28 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/04 10:53:17 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"
/* 
char	*ft_strdup_m(char *str)
{
	char *cmd;
	int len;
	int x;

	x = -1;
	len = 0;
	while (str[len] && ft_strncmp(str + len, "/bin/", 5) != 0)
		len++;
	if (len != ft_strlen(str))
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
	//printf("\n\n[%d][%d]\n", len , ft_strlen(str));
	if (len != ft_strlen(str))
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
	if (cmd_p == NULL && cmd_m == NULL)
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
*/
char **new_args(char **args)
{
	char **str;
	int x;

	x = 0;
	while (args[x])
		x++;
	if (!(str = malloc(sizeof(x + 2))))
		return (NULL);
	x = 0;
	str[x] = "";
	while (args[x])
	{
		str[x + 1] = args[x];
		x++;
	}
	str[x + 1] = NULL;
/*   	x = -1;
	while (args[++x])
		printf("arg = [%s]\n", args[x]);
	printf("\n"); */
/* 
	x = -1;
	while (str[++x])
		printf("str = [%s]\n", str[x]);
	//printf("str = [%s]\n", str[x + 1]);  */
	return (str);
}
 

char 	*get_path(t_set *set, char **old_args, char **envp)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;
	int 			valid;
	char **args;
	args = new_args(old_args);
	valid = 0;
	//printf("\n\n[%s]--[%s]\n\n\n", cmd_m, cmd_p);
/* 	if (cmd_p == NULL && cmd_m == NULL)
		return (NULL); */
	folder = opendir("/bin/");
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)))
	{
		if (ft_strcmp(item->d_name, set->cmd) == 0)
			valid = 1;
	}
	closedir(folder);

	
/* 	int x = -1;
	while (args[++x])
		printf("arg = [%s]\n", args[x]);
	printf("arg = [%s]\n", args[x + 1]); */
	int ret = 0;
	//int pid = fork();
	//printf("[%d]\n", pid);
	if (valid == 1 )//&& pid == 0)
	{
		//printf("OUI\n");
		set->exit_val = execve(ft_strjoin("/bin/", set->cmd), args , envp);
		//printf("exit = [%d]\n", set->exit_val);
		//return (set->cmd);
		exit(0);
	}
	//else
	//	waitpid(pid, &ret, 0);
	return (NULL);
}

char 	*get_path_chemin(t_set *set, char **old_args, char **envp, int len)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;
	int 			valid;
	char **args;
	args = new_args(old_args);
	valid = 0;
	int i = 0;

	if (!(path = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (set->cmd[i] && ft_strncmp(set->cmd + i, set->cmd + len, ft_strlen(set->cmd + len)))
	{
		path[i] = set->cmd[i];
		i++;
	}
	path[i] = '\0';
	//printf("cmd = [%s][%s][%d]\n", path , set->cmd + len, len);
	folder = opendir(path);
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)))
	{
		if (ft_strcmp(item->d_name, set->cmd + len) == 0)
			valid = 1;
	}
	closedir(folder);

	
/* 	int x = -1;
	while (args[++x])
		printf("arg = [%s]\n", args[x]);
	printf("arg = [%s]\n", args[x + 1]); */
	int ret = 0;
	//int pid = fork();
	//printf("[%d]\n", pid);
	if (valid == 1 )//&& pid == 0)
	{
		//printf("OUI\n");
		set->exit_val = execve(ft_strjoin(path, set->cmd + len), args , envp);
		//printf("exit = [%d]\n", set->exit_val);
		//return (set->cmd);
		exit(0);
	}
	//else
	//	waitpid(pid, &ret, 0);
	return (NULL);
}

int		bash_cmd(t_set *set)
{
	char *path;
	int x = 0;
	int len = 0;
	int chemin = 0;
	while (set->cmd[x])
	{
		if (ft_strncmp("/bin/", set->cmd + x, 5) == 0)
			chemin = 1;
		if (chemin == 0)
			len++;
		x++;
	}
	if (chemin == 0)
		path = get_path(set, set->arg, set->envp);
	else
		path = get_path_chemin(set, set->arg, set->envp, len + 5);

	//if (path == NULL)
	//	return (1); 
	//printf("{%s}{%s}\n", path, set->str);
/* 	while (set->arg[++x])
		//printf("arg = [%s]\n", set->arg[x]);
	if	(path != NULL)
	{
		execve(path, set->arg, set->envp);
	} */
	return (1);
}