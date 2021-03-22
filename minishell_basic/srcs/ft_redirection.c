/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:52:30 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/22 15:36:04 by phbarrad         ###   ########.fr       */
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

int		dolars_namefile(char *src, t_set *set, int a)
{
	char	*dol;
	int		i;

	//printf("start string : {%s}\n", src);
	dol = dolars_redirect(src, set);
	set->dol_amb = ft_strdup(dol);
	//printf("dol = {%s}\n", dol);
	dol = change_dol(dol, set);
	//printf("dol = {%s}\n", dol);
	i = 0;
	while (dol[i])
	{
		if (a == 0 && ft_iswhite(dol[i]) == 1)
			return (-2);
		set->word_tmp = add_letter(set->word_tmp, dol[i]);
		i++;
	}
	if (dol)
		free(dol);
	if (set->dol_amb)
		free(set->dol_amb);
	return (0);
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

char	*get_namefile(char *src, t_set *set, int i)
{
	char	*res;
	int		exit;

	set->y = i + 1;
	set->word_tmp = ft_strdup("");
	while ((src[set->y] == ' ' || src[set->y] == '\t') && src[set->y])
		set->y++;
	exit = 0;
	while (exit == 0)
	{
		if (src[set->y] == '\'')
			exit = search_quotes(src, set, '\'');
		else if (src[set->y] == '\"')
		{
			exit = change_quot_dol(src, set);
		}
		else if (src[set->y] == '$')
		{
			exit = dolars_namefile(src, set, 0);
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
		if ((src[set->y] == ' ' || src[set->y] == '\t' || !src[set->y] || src[set->y] == '<' || src[set->y] == '>') && exit == 0)				// devrais pas arriver
		{
			//printf("\n\nENTER\n\n");
			exit = 1;
		}
	}
	if (exit == -2)
		set->amb = 1;				// mouais
	else if (exit == -1)
		set->err_quote = 1;				// mouais
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

int		err_folder(t_set *set, char *namefile)
{
	char **args;
	char *tmp;
	char *tmp2;
	char *tmp3;
	int i;

	tmp3 = ft_strdup("");
	tmp = ft_strdup("");
	tmp2 = NULL;
	i = 0;
	args = ft_split(namefile, '/');
	while (args[i + 1])
	{
		if (i > 0)
			tmp = ft_strjoin(tmp3, "/");
		free(tmp3);
		tmp2 = ft_strjoin(tmp, args[i]);
		tmp3 = ft_strdup(tmp2);
		free(tmp);
		if (is_dir(tmp2) == 0)
		{
			set->exit_val = 4;
			ft_free_dbtab(args);
			free(tmp2);
			free(tmp3);
			return (1);
		}
		free(tmp2);
		i++;
	}
	if (i == 0 && is_dir(args[i]) == 0 && args[i][ft_strlen(args[i]) - 1] == '/')
	{
		//set->exit_val = 4;		//plus tard en fait
		//printf("ouimaisnon\n");
		free(tmp3);
		return (1);
	}
	return (0);
}

void	create_file(char *namefile, t_set *set, int a)
{
	ifclose(set->fdout);
	if (err_folder(set, namefile) == 1)
		set->not_exist = 1; // to do return err value	
	if (a == 1)
	{
		if ((set->fdout = open(namefile, O_CREAT | O_WRONLY | O_TRUNC, 00700)) == -1) // check fdout
			set->not_exist = 1;
	}
	else if (a == 2)
	{
		if ((set->fdout = open(namefile, O_CREAT | O_WRONLY | O_APPEND, 00700)) == -1) // check fdout
			set->not_exist = 1;
	}
	if (set->not_exist == 0)
		free(namefile);
	dup2(set->fdout, STDOUT);
}

void	change_stdin(char *namefile, t_set *set)
{
	close(set->fdin);
	if ((set->fdin = open(namefile, O_RDONLY, 00700)) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR); // error
		ft_putstr_fd(namefile, STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		set->stop = 1;
		set->exit_val = 1;
		set->bleu = 1;
	}
	if (set->not_exist == 0)
		free(namefile);
	dup2(set->fdin, STDIN);
}

void	err_amb(t_set *set)
{
	ft_putstr_fd("minishell: $", STDERR); // error
	ft_putstr_fd(set->dol_amb, STDERR);
	ft_putstr_fd(": ambiguous redirect\n", STDERR);
	free(set->dol_amb);
	set->stop = 1;
	set->exit_val = 1;
	set->bleu = 1;
}

void	err_notexist(t_set *set, char *namefile)
{
	ft_putstr_fd("minishell: ", STDERR); // error
	ft_putstr_fd(namefile, STDERR);
	ft_putstr_fd(": No such file or directory\n", STDERR);
	free(namefile);
	set->stop = 1;
	set->exit_val = 4;
	set->bleu = 1;
}

char	*redirection(char *src, t_set *set)
{
	int		i;
	char	*res;
	char	*namefile;
	int		a;

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
			//printf("ENTER1\n");
			//printf("SALUT\n");
			namefile = get_namefile(res, set, i + 1);
			if (set->amb == 0 && set->err_quote == 0)
			{
				res = get_newcmd(res, set, i);
				create_file(namefile, set, 2);
				i = -1;
			}
		}
		else if (res[i] == '>' && antislash_pair(res, i) == 1)
		{
			//printf("ENTER2\n");
			namefile = get_namefile(res, set, i);
			if (set->amb == 0 && set->err_quote == 0)
			{
				res = get_newcmd(res, set, i);
				//printf("namefile       = {%s}\n", namefile);
				// TODO if quote has been close
				// TODO if namefile is empty
				create_file(namefile, set, 1);
				i = -1;
			}
		}
		else if (res[i] == '<' && antislash_pair(res, i) == 1)
		{
			//printf("ENTER3\n");
			namefile = get_namefile(res, set, i);
			if (set->amb == 0 && set->err_quote == 0)
			{
				//printf("namefile = {%s}\n", namefile);
				res = get_newcmd(res, set, i);
				//printf("new cmd = {%s}\n", res);
				change_stdin(namefile, set);
				i = -1;
			}
		}
		//printf("res[i] = {%c} | res = {%s} | i = %d\n", res[i], res, i);
		i++;
		if (set->amb == 1)
			err_amb(set);
		if (set->not_exist == 1)
			err_notexist(set, namefile);
		//if (namefile)
			//free(namefile);
	}
	//printf("res = {%s}\n", res);
	return (res);
}