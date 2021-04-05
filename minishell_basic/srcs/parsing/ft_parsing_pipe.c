/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:22:36 by tsannie           #+#    #+#             */
/*   Updated: 2021/04/05 12:24:34 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

int		is_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i += 2;
		else if (str[i] == '\'' || str[i] == '\"')
			i = forwar_quote(str, i) + 1;
		else if (str[i] == '|')
			return (1);
		else
			i++;
	}
	return (0);
}

char	*new_pipe(char *str, t_set *set)
{
	char	*tmp;
	int		len;

	len = set->p;
	while (str[set->p] && str[set->p] != '|')
	{
		if (str[set->p] == '\\')
			set->p += 2;
		else if ((str[set->p] == '\'' || str[set->p] == '\"')
			&& antislash_pair(str, set->p) == 1)
			set->p = forwar_quote(str, set->p) + 1;
		else
			set->p++;
	}
	len = (set->p - len) + 1;
	set->p++;
	if (!(tmp = malloc(sizeof(char) * len)))
		return (NULL);
	ft_strlcpy(tmp, &str[set->p - (len)], len);
	return (tmp);
}

char	**split_pipe(char *str, t_set *set)
{
	char	**res;
	char	*add_this;
	int		i;

	if (!(res = malloc(sizeof(char*) * 1)))
		return (NULL);
	res[0] = 0;
	i = 1;
	while (set->p < (int)ft_strlen(str))
	{
		add_this = new_pipe(str, set);
		res = addword(res, i, add_this);
		i++;
		free(add_this);
	}
	return (res);
}
