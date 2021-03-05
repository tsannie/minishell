/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:52:30 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/05 10:44:31 by phbarrad         ###   ########.fr       */
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
	return (res);
}

void	create_file(char *namefile)
{
	int fd;

	if (namefile)
	{
		if ((fd = open(namefile, O_CREAT)) == -1)
			return ;
		close(fd);
		free(namefile);
	}
}

char	*redirection(char *src, t_set *set)
{
	char	*res;
	char	*namefile;
	int		a;

	a = is_present(src, '>');
	//printf("\n\n\na = %d\n\n\n", a);
	if (a != 0)
	{
		//printf("ex cmd = {%s}\n", src);
		namefile = get_namefile(src, set, a);			// pas bien test
		//printf("\n\nnamefile = |%s|\n\n", namefile);
		res = get_newcmd(src, set, a);
		create_file(namefile);
		//printf("new cmd = {%s}\n", res);
	}
	else
		res = ft_strdup(src);
	return (res);
}