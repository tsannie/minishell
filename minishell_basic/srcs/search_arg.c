/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 08:17:41 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/25 07:26:34 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char	**addword(char **res, int nb_word, char *word)
{
	char	**new;
	int		i;

	if (!(new = malloc(sizeof(char*) * (nb_word + 1))))
		return (NULL);
	i = 0;
	while (res[i])
	{
		new[i] = ft_strdup(res[i]);
		i++;
	}
	new[i] = ft_strdup(word);
	new[nb_word] = 0;
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (new);
}

int		search_quotes(const char *src, t_set *set, char a)
{
	if (src[set->y] == a)
	{
		set->y++;
		while (src[set->y] && src[set->y] != a)
		{
			if (src[set->y] == '\\' && (src[set->y + 1] == '\\'
			|| src[set->y + 1] == '$' || src[set->y + 1] == '\"') && a == '\"')
			{
				set->word_tmp = add_letter(set->word_tmp, src[set->y + 1]);
				set->y = set->y + 2;
			}
			else
			{
				set->word_tmp = add_letter(set->word_tmp, src[set->y]);
				set->y++;
			}
		}
		if (src[set->y] != a)
			return (-1);
		set->y++;
	}
	return (0);
}

void	search_basic(const char *str, t_set *set)
{
	while (str[set->y] && ft_istab(str[set->y]) != 1
		&& str[set->y] != '\'' && str[set->y] != '\"')
	{
		if ((str[set->y] == '\\' && str[set->y + 1]))
		{
			set->word_tmp = add_letter(set->word_tmp, str[set->y + 1]);
			set->y = set->y + 2;
		}
		else
		{
			set->word_tmp = add_letter(set->word_tmp, str[set->y]);
			set->y++;
		}
	}
}

int		new_arg(char *str, int exit, t_set *set)
{
	exit = 0;
	set->word_tmp = ft_strdup("");
	while (exit == 0)
	{
		if (str[set->y] == '\'')
			exit = search_quotes(str, set, '\'');
		else if (str[set->y] == '\"')
			exit = search_quotes(str, set, '\"');
		else if (ft_istab(str[set->y]) != 1 && str[set->y])
			search_basic(str, set);
		if ((ft_istab(str[set->y]) == 1 || !str[set->y]) && exit == 0)
			exit = 1;
	}
	while (ft_istab(str[set->y]) == 1 && str[set->y])
		set->y++;
	if (!str[set->y] && exit == 0)
		exit = 1;
	set->nb_word++;
	set->arg = addword(set->arg, set->nb_word, set->word_tmp);
	free(set->word_tmp);
	return (exit);
}

void	search_arg(char *str, t_set *set)
{
	int		exit;

	set->nb_word = 0;
	exit = 2;
	while (ft_istab(str[set->y]) == 1 && str[set->y])
		set->y++;
	if (!(set->arg = malloc(sizeof(char*) * 1)))
		return ;
	set->arg[0] = 0;
	while (str[set->y])
		exit = new_arg(str, exit, set);
	if (exit == -1)
		set->err_quote = 1;
}
