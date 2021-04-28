/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_semicolon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 07:47:01 by tsannie           #+#    #+#             */
/*   Updated: 2021/04/28 14:52:25 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void	add_inquote(char *str, t_set *set, char a)
{
	if (str[set->y] == '\\' && (str[set->y + 1] == '\\'
		|| str[set->y + 1] == '$') && a == '\"')
	{
		set->word_tmp = add_letter(set->word_tmp, str[set->y]);
		set->word_tmp = add_letter(set->word_tmp, str[set->y + 1]);
		set->y = set->y + 2;
	}
	else if (str[set->y] == '\\' && str[set->y + 1] == a && a != '\'')
	{
		set->word_tmp = add_letter(set->word_tmp, str[set->y]);
		set->word_tmp = add_letter(set->word_tmp, str[set->y + 1]);
		set->y = set->y + 2;
	}
	else
	{
		set->word_tmp = add_letter(set->word_tmp, str[set->y]);
		set->y++;
	}
}

int		open_quote(char *str, t_set *set, char a)
{
	if (str[set->y] == a)
	{
		set->word_tmp = add_letter(set->word_tmp, str[set->y]);
		set->y++;
		while (str[set->y] && str[set->y] != a)
		{
			add_inquote(str, set, a);
		}
		if (str[set->y] != a)
			return (-1);
		else
		{
			set->word_tmp = add_letter(set->word_tmp, str[set->y]);
			set->y++;
		}
	}
	return (0);
}

int		add_all(char *str, t_set *set, int exit)
{
	while (str[set->y] && str[set->y] != '\'' && str[set->y] != '\"'
		&& str[set->y] != ';')
	{
		if ((str[set->y] == '\\' && str[set->y + 1]))
		{
			set->word_tmp = add_letter(set->word_tmp, str[set->y]);
			set->word_tmp = add_letter(set->word_tmp, str[set->y + 1]);
			set->y = set->y + 2;
		}
		else
		{
			set->word_tmp = add_letter(set->word_tmp, str[set->y]);
			set->y++;
		}
	}
	if (str[set->y] == ';')
	{
		set->y++;
		return (1);
	}
	return (exit);
}

int		loop_split(char *str, t_set *set, int exit)
{
	if (str[set->y] == '\'')
		exit = open_quote(str, set, '\'');
	else if (str[set->y] == '\"')
	{
		exit = open_quote(str, set, '\"');
	}
	else
		exit = add_all(str, set, exit);
	return (exit);
}

char	**split_semicolon(char *str, t_set *set)
{
	char	**res;
	int		exit;
	int		nb_word;

	nb_word = 0;
	exit = 2;
	set->y = 0;
	if (!(res = malloc(sizeof(char*) * 1)))
		return (NULL);
	res[0] = 0;
	while (str[set->y])
	{
		exit = 0;
		set->word_tmp = ft_strdup("");
		while (exit == 0 && str[set->y])
			exit = loop_split(str, set, exit);
		if (!str[set->y] && exit == 0)
			exit = 1;
		nb_word++;
		res = addword(res, nb_word, set->word_tmp);
		ffree(set->word_tmp);
	}
	if (exit == -1)
		set->err_quote = 1;
	return (res);
}
