/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:52:00 by tsannie           #+#    #+#             */
/*   Updated: 2021/04/28 14:52:25 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

char	*add_letter(char *str, char a)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(str) + 2;
	if (!(res = malloc(sizeof(char) * len)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = a;
	res[len - 1] = '\0';
	if (str)
		free(str);
	return (res);
}

void	search_cmd(const char *src, t_set *set)
{
	int		exit;

	set->y = 0;
	set->word_tmp = ft_strdup("");
	while (ft_istab(src[set->y]) == 1 && src[set->y])
		set->y++;
	exit = 0;
	while (exit == 0)
	{
		if (src[set->y] == '\'')
			exit = search_quotes(src, set, '\'');
		else if (src[set->y] == '\"')
			exit = search_quotes(src, set, '\"');
		else if (ft_istab(src[set->y]) != 1)
			search_basic(src, set);
		if ((ft_istab(src[set->y]) == 1 || !src[set->y]) && exit == 0)
			exit = 1;
	}
	if (exit == -1)
		set->err_quote = 1;
	set->cmd = ft_strdup(set->word_tmp);
	ffree(set->word_tmp);
}
