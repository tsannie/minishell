/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:13:39 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/29 15:11:14 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

char			*ft_getenv(int i)
{
	char		*cwd;
	char		*result;
	char		buff[4096 + 1];
	int			e;
	int			r;

	e = -2;
	r = -3;
	cwd = getcwd(buff, 4097);
	result = malloc(sizeof(char) * (ft_strlen(cwd) + 1));
	while (cwd[++i])
	{
		if (cwd[i] == '/')
			e++;
	}
	while (e > 0)
	{
		r += 3;
		result[r] = '.';
		result[r + 1] = '.';
		result[r + 2] = '/';
		e--;
	}
	result[r + 3] = '\0';
	return (result);
}

void			error_msg(t_set *set)
{
	ft_putstr_fd("minishell: cd: ", STDERR);
	ft_putstr_fd(set->arg[0], STDERR);
	if (errno == EACCES)
		ft_putstr_fd(": Permission denied\n", STDERR);
	else if (is_dir_present(set->pwd, set->arg[0]) == 1)
		ft_putstr_fd(": Not a directory\n", STDERR);
	else
		ft_putstr_fd(": No such file or directory\n", STDERR);
	set->exit_val = 1;
	set->bleu = 1;
}

int				ft_chem(t_set *set)
{
	int			valid;
	int			i;

	i = -1;
	valid = 0;
	if (set->arg[0] != NULL)
		valid = chdir(set->arg[0]);
	if (valid == -1 && set->arg[0] != NULL)
	{
		if (ft_strlen(set->arg[0]) == 0)
			return (-4);
		error_msg(set);
		return (-1);
	}
	if (set->arg[0] == NULL)
		return (chdir(ft_getenv(i)));
	return (0);
}

char			*parc_env(t_set *set)
{
	int			x;

	x = 0;
	while (set->envp[x])
	{
		if (ft_strncmp(set->envp[x], "PWD=", 4) == 0)
			return (ft_strdup(set->envp[x] + 4));
		x++;
	}
	return (set->pwd);
}

int				ft_cd(t_set *set)
{
	char		buff[4096 + 1];
	int			ret;
	char		*temp;

	if (set->pwd)
		free(set->pwd);
	set->pwd = parc_env(set);
	ret = ft_chem(set);
	if (ret != -1)
	{
		temp = ft_strdup(set->pwd);
		if (set->old_pwd)
			free(set->old_pwd);
		set->old_pwd = ft_strjoin("OLDPWD=", temp);
		ft_hideenv(set->old_pwd, set);
		ft_modenv(set->old_pwd, set);
		free(temp);
	}
	free(set->pwd);
	set->pwd = ft_strdup(getcwd(buff, 4097));
	temp = ft_strdup(set->pwd);
	free(set->pwd);
	set->pwd = ft_strjoin("PWD=", temp);
	ft_hideenv(set->pwd, set);
	ft_modenv(set->pwd, set);
	free(temp);
	return (ret);
}
