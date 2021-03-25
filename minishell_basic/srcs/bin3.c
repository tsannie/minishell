/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:27:42 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/24 13:25:48 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int					exec_bin(t_set *set, char *path, char *cmd)
{
	int				pid;
	char			**args;
	int				r;
	char			*ttm;
	int				g;
	int				ret;

	if (check_sh(set, path) == 1)
		return (1);
	if (ft_strncmp(cmd, "whoami", ft_strlen(cmd)) == 0)
	{
		free(cmd);
		cmd = ft_strdup(set->cmd);
	}
	pid = fork();
	args = new_args(set->arg, cmd);
	ret = 0;
	g = 0;
	r = 0;
	if (path != NULL && pid == 0)
	{
		if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		{
			ttm = joinf("_=", path, "", "");
			ft_modenv(ttm, set);
			g = 1;
			execve(path, args, set->envp);
		}
		else
			execve(path, args, set->envp);
	}
	else
		waitpid(pid, &ret, 0);
	if (ret == 256)
		set->exit_val = 1;
	else if (ret == 54784)
		set->exit_val = 1;
	if (set->exit_val == 1)
		set->bleu = 1;
	if (g == 1)
	{
		if (set->pathbc != NULL)
		{
			free(set->pathbc);
			set->pathbc = NULL;
		}
		if (ttm)
			free(ttm);
	}
	r = -1;
	while (args[++r])
		free(args[r]);
	free(args);
	return (0);
}