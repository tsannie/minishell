/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportpe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:55:14 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/23 13:32:07 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char			*st_moin_pe(char *str)
{
	int i;
	int e;
	char *new;

	e = 0;
	i = 0;
	while (ft_strncmp(str + i, "+=", 2) != 0 && str[i])
		i++;
	while (str[i + e])
		e++;
	i += 2;
	if (!(new = malloc(sizeof(char) * (e))))
		return (NULL);
	e = 0;
	while (str[i + e])
	{
		new[e] = str[i + e];
		e++;
	}
	new[e] = '\0';
	return (new);
}

char			*st_moin_p(char *str)
{
	int i;
	int e;
	char *new;

	e = 0;
	i = 0;
	if (!(new = malloc(sizeof(char) * (ft_strlen(str)))))
		return (NULL);
	while (str[i + e])
	{
		if (str[i + e] == '+')
			i++;
		new[e] = str[i + e];
		e++;
	}
	new[e] = '\0';
	return (new);
}


int				ft_eghide(char *arg, t_set *set)
{
	int			i;
	int			act;
	char		*str;
	char		*tmp;

	act = 0;
	str = double_slash(arg);
	i = 0;
	while (set->hide_envp[i] != NULL)
	{
		if(ncmpelp(str, set->hide_envp[i]) == 0)
		{
			str = st_moin_pe(str);
			tmp = ft_strjoin(set->hide_envp[i], str);
			free(set->hide_envp[i]);
			set->hide_envp[i] = ft_strdup(tmp);
			free(tmp);
			act = 1;
		}
		i++;
	}
	if (act == 0)
	{	
		tmp = ft_strdup(str);
		free(str);
		str = st_moin_p(tmp);
		free(tmp);
		set->hide_envp = addword(set->hide_envp,i + 1, set, str);
		set->hide_envp[i + 1] = NULL;
	}
 	i = 0;
	free(str);
	return (0);
}

int 			ft_egenv(char *str, t_set *set)
{
	int			i;
	int			act;
	char		*tmp;

	act = 0;
	i = 0;
	while (set->envp[i] != NULL)
	{
		if(ncmpelp(str, set->envp[i]) == 0)
		{
			str = st_moin_pe(str);
			tmp = ft_strjoin(set->envp[i], str);
			free(set->envp[i]);
			set->envp[i] = ft_strdup(tmp);
			free(tmp);
			act = 1;
		}
		i++;
	}
	if (act == 0)
	{
		tmp = ft_strdup(str);
		free(str);
		str = st_moin_p(tmp);
		free(tmp);
		set->envp = addword(set->envp, i + 1, set, str);
		set->envp[i + 1] = NULL;
	}
	return (0);
}