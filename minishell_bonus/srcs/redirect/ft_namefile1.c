/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_namefile1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:04:47 by tsannie           #+#    #+#             */
/*   Updated: 2021/04/07 10:32:15 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

void	dolars_namefile(char *src, t_set *set, int a)
{
	char	*dol;
	int		i;

	dol = dolars_redirect(src, set);
	refresh_amb(dol, set);
	dol = change_dol(dol, set);
	i = 0;
	while (dol[i])
	{
		if (a == 0 && ft_iswhite(dol[i]) == 1)
			set->amb = 1;
		set->word_tmp = add_letter(set->word_tmp, dol[i]);
		i++;
	}
	free(dol);
}

int		change_quot_dol(const char *src, t_set *set)
{
	set->y++;
	while (src[set->y] && src[set->y] != '\"')
	{
		if (src[set->y] == '\\' && (src[set->y + 1] == '\\'
		|| src[set->y + 1] == '$' || src[set->y + 1] == '\"'))
		{
			set->word_tmp = add_letter(set->word_tmp, src[set->y + 1]);
			set->y = set->y + 2;
		}
		else if (src[set->y] == '$')
			dolars_namefile((char*)src, set, 1);
		else
		{
			set->word_tmp = add_letter(set->word_tmp, src[set->y]);
			set->y++;
		}
	}
	if (src[set->y] != '\"')
		return (-1);
	set->y++;
	return (0);
}

void	search_basic_redirect(const char *str, t_set *set)
{
	while (str[set->y] && str[set->y] != ' ' && str[set->y] != '\''
		&& str[set->y] != '\"' && str[set->y] != '$'
		&& str[set->y] != '<' && str[set->y] != '>')
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

int		loop_namefile(char *src, t_set *set, int exit)
{
	if (src[set->y] == '\'')
		exit = search_quotes(src, set, '\'');
	else if (src[set->y] == '\"')
		exit = change_quot_dol(src, set);
	else if (src[set->y] == '$')
		dolars_namefile(src, set, 0);
	else if (src[set->y] != ' ')
		search_basic_redirect(src, set);
	if ((src[set->y] == ' ' || src[set->y] == '\t' || !src[set->y]
	|| src[set->y] == '<' || src[set->y] == '>') && exit == 0)
		exit = 1;
	return (exit);
}

char	*get_namefile(char *src, t_set *set, int i)
{
	char	*res;
	int		exit;

	set->y = i + 1;
	set->word_tmp = ft_strdup("");
	while (ft_istab(src[set->y]) == 1 && src[set->y])
		set->y++;
	exit = 0;
	while (exit == 0)
		exit = loop_namefile(src, set, exit);
	if (exit == -1)
		set->err_quote = 1;
	res = ft_strdup(set->word_tmp);
	ffree(set->word_tmp);
	return (res);
}
