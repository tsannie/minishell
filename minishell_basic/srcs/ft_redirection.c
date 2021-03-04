/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:52:30 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/04 16:14:50 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int		is_present(char *src, char a)
{
	int		i;

	i = 0;
	//printf("src = {%s}\n", src);
	while (src[i])
	{
		//printf("src[i] = {%c}", src[i]);
		if (src[i] == '\'' && antislash_pair(src, i) == 1)
		{
			i++;
			while (src[i] && src[i] != '\'')
			{
				i++;
			}
		}
		else if (src[i] == '\"' && antislash_pair(src, i) == 1)
		{
			i++;
			while (src[i] && src[i] != '\"')
			{
				i++;
			}
		}
		else if (src[i] == a)
		{
			//printf("i = %d\n", i);
			return (i);
		}
		i++;
	}
	return (0);
}

void	dolars_namefile(const char *src, t_set *set)
{
	char	*dol;
	int		i;

	dol = dolars_find((char*)&src[set->y], set);
	dol = change_dol(dol, set);
	i = 0;
	while (dol[i])
	{
		set->word_tmp = add_letter(set->word_tmp, dol[i]);
		i++;
	}
}

char	*get_namefile(char *src, t_set *set, int i)
{
	char	*res;
	int		exit;

	set->y = i + 1;
	set->word_tmp = ft_strdup("");
	while (src[set->y] == ' ' && src[set->y])
		set->y++;
	exit = 0;
	while (exit == 0)
	{
		if (src[set->y] == '\'')
			exit = search_quotes(src, set, '\'');
		else if (src[set->y] == '\"')
			exit = search_quotes(src, set, '\"');
		else if (src[set->y] == '$')
			dolars_namefile(src, set);
		else if (src[set->y] != ' ')
		{
			while (src[set->y] && src[set->y] != ' ' && src[set->y] != '\'' && src[set->y] != '\"' && src[set->y] != '$')
			{
				if ((src[set->y] == '\\' && src[set->y + 1]))
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
		}
		if ((src[set->y] == ' ' || !src[set->y]) && exit == 0)
			exit = 1;
	}
	if (exit == -1)
		set->err_quote = 1;
	res = ft_strdup(set->word_tmp);
	free(set->word_tmp);
	return (res);
}

char	*get_newcmd(char *src, t_set *set, int i)
{
	char	*res;
	int		e;

	res = ft_strdup("");
	e = 0;
	while (e != i)
	{
		res = add_letter(res, src[e]);
		e++;
	}
	e = set->y;
	while (src[e])
	{
		res = add_letter(res, src[e]);
		e++;
	}
	free(src);
	return (res);
}

char	*redirection(char *src, t_set *set)
{
	char	*res;
	char	*namefile;
	int		a;

	a = is_present(src, '>');
	printf("\n\n\na = %d\n\n\n", a);
	if (a != 0)
	{
		printf("ex cmd = {%s}\n", src);
		namefile = get_namefile(src, set, a);			// pas bien test
		printf("\n\nnamefile = |%s|\n\n", namefile);
		free(namefile); 			// en vrai faut free
		res = get_newcmd(src, set, a);
		printf("new cmd = {%s}\n", res);
	}
	else
		res = ft_strdup(src);
	return (res);
}