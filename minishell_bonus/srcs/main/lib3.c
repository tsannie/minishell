/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:07:05 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/07 10:32:15 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void			add_exval(t_set *set)
{
	char		*tmp;

	tmp = ft_itoa(set->exit_val);
	if (set->exit_v)
		free(set->exit_v);
	set->exit_v = ft_strjoin("?=", tmp);
	free(tmp);
	ft_hideenv(set->exit_v, set);
}

char			*maj_to_min(char *str)
{
	int			i;
	char		*res;

	i = 0;
	res = ft_strdup(str);
	while (res[i])
	{
		if (res[i] >= 'A' && res[i] <= 'Z')
			res[i] = res[i] + 32;
		i++;
	}
	return (res);
}

int				eglinstr(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int				check_last(t_set *set)
{
	int			i;

	if (ft_strncmp(set->str, "$_", ft_strlen(set->str)) == 0)
		return (1);
	i = ft_strlen(set->str) - 1;
	while (set->str[i] == ' ' || set->str[i] == '\t')
		i--;
	if (ft_strncmp(set->str + i - 1, "$_", 2) == 0)
		return (1);
	return (0);
}
