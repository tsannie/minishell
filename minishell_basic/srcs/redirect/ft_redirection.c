/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:52:30 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/29 15:11:14 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish.h"

char	*dolars_redirect(char *src, t_set *set)
{
	char	*res;

	set->y++;
	res = ft_strdup("");
	if (ft_isdigit(src[set->y]) == 1 || src[set->y] == '?')
	{
		res = add_letter(res, src[set->y]);
		set->y++;
		return (res);
	}
	if (src[set->y] != '\"' && src[set->y] != '\'')
	{
		while (src[set->y] && (ft_isalnum(src[set->y]) == 1 || src[set->y] == '_'
			|| src[set->y] == '?'))
		{
			res = add_letter(res, src[set->y]);
			set->y++;
		}
	}
	return (res);
}

void	refresh_amb(char *dol, t_set *set)
{
	char	*res;

	res = ft_strjoin("$", dol);
	//printf("res = {%s}\n", res);

	set->dol_amb = ft_strjoin_free(set->dol_amb, res);
	//printf("dol_amb = {%s}\n", res);
	free(res);
}

void	dolars_namefile(char *src, t_set *set, int a)
{
	char	*dol;
	int		i;

	//printf("\n\n\nHERE\n\n\n");
	dol = dolars_redirect(src, set);
	//printf("dol = {%s}\n", dol);
	refresh_amb(dol, set);		// free si tout va bien
	//printf("dol_amb = %s\n", set->dol_amb);
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
		if (src[set->y] == '\\' && (src[set->y + 1] == '\\' || src[set->y + 1] == '$'
			|| src[set->y + 1] == '\"'))
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
		|| src[set->y] == '<' || src[set->y] == '>') && exit == 0)				// devrais pas arriver
		{
			//printf("\n\nENTER\n\n");
			exit = 1;
		}
	}
	if (exit == -1)
		set->err_quote = 1;				// mouais
	res = ft_strdup(set->word_tmp);
	ffree(set->word_tmp);
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

void	create_file(char *namefile, t_set *set, int a) // >
{
	int i;

	i = 0;
	ifclose(set->fdout);
	set->not_exist = err_folder(set, namefile, i);
	//printf("err_folder = [%d]\n", set->not_exist);
	if (a == 1)
	{
		if ((set->fdout = open(namefile, O_CREAT | O_WRONLY | O_TRUNC, 00700)) == -1)
		{// check fdout
			if (set->not_exist == 1)
				set->not_exist = 3;
			else if (set->not_exist == 4)
				set->not_exist = 1;
			else
				set->not_exist = 2;
		}
	}
	else if (a == 2)
	{
		if ((set->fdout = open(namefile, O_CREAT | O_WRONLY | O_APPEND, 00700)) == -1) // check fdout
			set->not_exist = 3;
	}
	if (set->not_exist == 0)
	{
		free(namefile);
		dup2(set->fdout, STDOUT);
	}
	else
		set->namefile = namefile;
}

void	change_stdin(char *namefile, t_set *set) // <
{
	ifclose(set->fdin);
	if ((set->fdin = open(namefile, O_RDONLY, 00700)) == -1)
		set->not_exist = 1;
	if (set->not_exist == 0)
	{
		free(namefile);
		dup2(set->fdin, STDIN);
	}
	else
		set->namefile = namefile;
}

void	err_amb(t_set *set)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(set->dol_amb, STDERR);
	ft_putstr_fd(": ambiguous redirect\n", STDERR);
	set->stop = 1;
	set->exit_val = 1;
	set->bleu = 1;
	ffree(set->dol_amb);
	set->dol_amb = NULL;
}

void	err_notexist(t_set *set)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(set->namefile, STDERR);
	if (set->not_exist == 1)
		ft_putstr_fd(": No such file or directory\n", STDERR);
	else if (set->not_exist == 2)
		ft_putstr_fd(": Is a directory\n", STDERR);
	else if (set->not_exist == 3)
		ft_putstr_fd(": Not a directory\n", STDERR);
	ffree(set->namefile);
	set->stop = 1;
	set->exit_val = 1;
	set->bleu = 1;
}

char	*simple_redirect(char *res, int i, t_set *set)
{
	char	*namefile;
	char	a;

	a = (res[i] == '>') ? '>' : '<';
	namefile = get_namefile(res, set, i);
	if (!namefile[0])
		set->amb = 1;
	if (set->amb == 1 && namefile)
		free(namefile);
	if (set->amb == 0 && set->err_quote == 0)
	{
		res = get_newcmd(res, set, i);
		if (a == '>')
			create_file(namefile, set, 1);
		else
			change_stdin(namefile, set);
		ffree(set->dol_amb);
		set->dol_amb = NULL;
	}
	return (res);
}

char	*double_redirect(char *res, int i, t_set *set)
{
	char	*namefile;

	namefile = get_namefile(res, set, i + 1);
	if (!namefile[0])
		set->amb = 1;
	if (set->amb == 1 && namefile)
		free(namefile);
	if (set->amb == 0 && set->err_quote == 0)
	{
		res = get_newcmd(res, set, i);
		create_file(namefile, set, 2);
		ffree(set->dol_amb);
		set->dol_amb = NULL;
	}
	return (res);
}

char	*redirection(char *src, t_set *set)
{
	int		i;
	char	*res;

	res = ft_strdup(src);
	i = 0;
	set->not_exist = 0;
	set->amb = 0;
	while (res[i] && set->stop == 0)
	{
		if ((res[i] == '\'' || res[i] == '\"') && antislash_pair(res, i) == 1)
			i = forwar_quote(res, i);
		else if (res[i] == '>' && res[i + 1] == '>' && antislash_pair(res, i) == 1)
		{
			res = double_redirect(res, i, set);
			i = -1;
		}
		else if ((res[i] == '>' || res[i] == '<') && antislash_pair(res, i) == 1)
		{
			res = simple_redirect(res, i, set);
			i = -1;
		}
		i++;
		if (set->amb == 1)
			err_amb(set);
		if (set->not_exist == 1 || set->not_exist == 2 || set->not_exist == 3)
			err_notexist(set);
	}
	add_exval(set);
	return (res);
}
