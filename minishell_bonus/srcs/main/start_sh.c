/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:12:51 by tsannie           #+#    #+#             */
/*   Updated: 2021/04/28 14:52:25 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void			get_lastcmd(t_set *set)
{
	int			i;
	char		*tmp;

	i = 0;
	while (set->arg[i])
		i++;
	if (set->arg[0] == NULL)
		tmp = ft_strdup(set->cmd);
	else if (i != 0)
		tmp = ft_strdup(set->arg[i - 1]);
	if (ft_strncmp(set->cmd, "export", ft_strlen(set->cmd)) == 0 &&
	eglinstr(tmp) == 1 && i != 0)
	{
		if (tmp)
			free(tmp);
		tmp = before_equale(set->arg[i - 1]);
	}
	ffree(set->lastcmd);
	set->lastcmd = ft_strjoin("_=", tmp);
	if (tmp)
		free(tmp);
	ft_hideenv(set->lastcmd, set);
	ft_modenv(set->lastcmd, set);
}

int				init_start(t_set *set)
{
	if (ft_streql(set->cmd, "exit") == 1)
		ft_eexit(set);
	if (set->bleu == 1)
	{
		set->exit_val = 0;
		set->bleu = 0;
	}
	if (set->err_quote == 1)
		return (ft_putstr_error_quote(set));
	else if (ft_streql(set->cmd, "export") == 1)
		return (ft_export(set));
	else if (ft_streql(set->cmd, "cd") == 1)
		return (ft_cd(set));
	else if (ft_streql(set->cmd, "pwd") == 1)
		return (ft_pwd(set));
	else if (ft_streql(set->cmd, "unset") == 1)
		return (ft_unset(set));
	else if (ft_streql(set->cmd, "echo") == 1)
		return (ft_echo(set));
	else if (ft_streql(set->cmd, "env") == 1)
		return (ft_env(set));
	else if (bash_cmd(set) == 0)
		return (0);
	return (1);
}

void			start_cmd(t_set *set)
{
	get_lastcmd(set);
	add_exval(set);
	if (init_start(set) == 0)
		;
	else if (ft_strlen(set->cmd) != 0 && set->ex_er == 0)
	{
		if (ft_strncmp(set->cmd + ft_strlen(set->cmd) - 1, "/",
		ft_strlen(set->cmd + ft_strlen(set->cmd) - 1)) == 0 &&
		set->exit_val != 3 && set->exit_val != 7)
			set->exit_val = 4;
		ft_putstr_not_found(set->cmd, set);
		set->bleu = 1;
	}
	set->ex_er = 0;
	if (set->bleu == 2)
		set->bleu = 1;
	if (set->path)
		free(set->path);
	set->path = ft_get_path(set->envp);
	if (set->all_path)
		ft_free_dbtab(set->all_path);
	set->all_path = ft_splitbc(set->path, ':');
	add_exval(set);
}

int				start_shell(int ac, char **av, t_set *set)
{
	int			ret;

	if (ac == 3)
		set->str = ft_strdup(av[2]);
	treat_cmd(set);
	ret = set->exit_val;
	return (ret);
}
