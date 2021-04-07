/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:24:42 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/07 10:32:15 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

int				ft_menv(char *str, t_set *set)
{
	int			i;

	i = 0;
	while (set->envp[i] != NULL)
		i++;
	set->envp = addword(set->envp, i + 1, str);
	return (0);
}

char			*ft_get_path(char **envp)
{
	int			i;
	char		*str;
	int			j;
	int			e;

	e = -1;
	j = 0;
	i = 0;
	if (envp[0] == NULL)
		return (ft_strdup(""));
	while (ft_strncmp("PATH=", envp[i], 5) != 0 && envp[i + 1])
		i++;
	if (envp[i + 1] == NULL && ft_strncmp("PATH=", envp[i], 5) != 0)
		return (NULL);
	while (envp[i][j] != '=' && envp[i][j])
		j++;
	if (!(str = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1 - j + 1))))
		return (NULL);
	while (envp[i][j + 1])
	{
		str[++e] = envp[i][j + 1];
		j++;
	}
	str[e + 1] = '\0';
	return (str);
}

char			*change_slash(char *str)
{
	int			i;
	char		*res;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == '\"' || str[i] == '$')
			res = add_letter(res, '\\');
		res = add_letter(res, str[i]);
		i++;
	}
	return (res);
}

char			**ft_strdup_dslash(char **envp)
{
	char		**hide_envp;
	int			y;
	int			len;

	len = 0;
	y = 0;
	while (envp[len] != NULL)
		len++;
	if (!(hide_envp = malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (envp[y])
	{
		hide_envp[y] = change_slash(envp[y]);
		y++;
	}
	hide_envp[y] = NULL;
	return (hide_envp);
}

void			ft_init_env(t_set *set)
{
	int			i;
	int			shlvl;
	int			pwd;

	shlvl = 0;
	pwd = 0;
	i = -1;
	while (set->envp[++i])
	{
		if (ft_strncmp("SHLVL=", set->envp[i], 6) == 0)
			shlvl = 1;
		if (ft_strncmp("PWD=", set->envp[i], 4) == 0)
			pwd = 1;
	}
	if (pwd == 0)
		ft_menv(ft_strjoin("PWD=", set->pwd), set);
	if (shlvl == 0)
		ft_menv(ft_strjoin("SHLVL=", set->shlvl), set);
	set->hide_envp = ft_strdup_dslash(set->envp);
}
