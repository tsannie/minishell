/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:52:30 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/09 16:41:09 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char	*dolars_redirect(char *src, t_set *set)
{
	char	*res;
	int		err;

	set->y++;
	res = ft_strdup("");
	err = 0;
	if (src[set->y] != '\"' &&  src[set->y] != '\'')
	{
		while (src[set->y] && (ft_isalnum(src[set->y]) == 1 || src[set->y] == '_')) // ATTENTION Y'EN A D'AUTRES !
		{
			res = add_letter(res, src[set->y]);
			set->y++;
		}
	}
	return (res);
}

void	dolars_namefile(char *src, t_set *set)
{
	char	*dol;
	int		i;

	//printf("start string : {%s}\n", src);
	dol = dolars_redirect(src, set);
	//printf("dol = {%s}\n", dol);
	dol = change_dol(dol, set);
	//printf("dol = {%s}\n", dol);
	i = 0;
	while (dol[i])
	{
		set->word_tmp = add_letter(set->word_tmp, dol[i]);
		i++;
	}
	if (dol)
		free(dol);
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
		{
			dolars_namefile(src, set);
			//printf("set->word_tmp = {%c}\n", set->word_tmp[set->y]);
		}
		else if (src[set->y] != ' ')
		{
			while (src[set->y] && src[set->y] != ' ' && src[set->y] != '\'' && src[set->y] != '\"' && src[set->y] != '$' && src[set->y] != '<' && src[set->y] != '>')
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
		if ((src[set->y] == ' ' || !src[set->y] || src[set->y] == '<' || src[set->y] == '>') && exit == 0)
		{
			//printf("\n\nENTER\n\n");
			exit = 1;
		}
	}
	if (exit == -1)
		set->err_quote = 1;
	res = ft_strdup(set->word_tmp);
	//printf("res = {%s}\n", res);
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

void	create_file(char *namefile, t_set *set, int a)
{
	int fd;

	if (namefile && a == 1)
	{
		if (set->fd != 1)
			close(set->fd);
		if ((set->fd = open(namefile, O_CREAT | O_WRONLY | O_TRUNC, 00700)) == -1) // do file
			return ;
		free(namefile);
	}
	else if (namefile && a == 2)
	{
		if (set->fd != 1)
			close(set->fd);
		if ((set->fd = open(namefile, O_CREAT | O_WRONLY | O_APPEND, 00700)) == -1) // do file
			return ;
		free(namefile);
	}
}

char	*redirection(char *src, t_set *set)
{
	int		i;
	char	*res;
	char	*namefile;
	int		a;

	res = ft_strdup(src);
	i = 0;
	while (res[i])
	{
		//printf("res[i] = {%c} | res = {%s} | i = %d\n", res[i], res, i);
		if ((res[i] == '\'' || res[i] == '\"') && antislash_pair(res, i) == 1)
			i = forwar_quote(res, set, i);
		else if (res[i - 1] != '>' && res[i] == '>' && res[i + 1] == '>' && res[i + 2] != '>')
		{
			//printf("SALUT\n");
			namefile = get_namefile(res, set, i + 1);
			res = get_newcmd(res, set, i);
			create_file(namefile, set, 2);
			i = -1;
		}
		else if (res[i - 1] != '>' && res[i] == '>' && res[i + 1] != '>')
		{
			namefile = get_namefile(res, set, i);
			res = get_newcmd(res, set, i);
			create_file(namefile, set, 1);
			i = -1;
		}
		i++;
	}
	//printf("res = {%s}\n", res);
	return (res);
}