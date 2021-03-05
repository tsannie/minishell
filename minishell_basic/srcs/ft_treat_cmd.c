/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 07:41:05 by tsannie           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/03/04 16:27:01 by phbarrad         ###   ########.fr       */
=======
/*   Updated: 2021/03/05 10:33:33 by tsannie          ###   ########.fr       */
>>>>>>> 15d7368af785d3a15646ef31ed2caa0c9a93ab0f
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char	*add_letter(char *str, char a)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(str) + 2;
	if (!(res = malloc(sizeof(char) * len)))
		return NULL;
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = a;
	res[len - 1] = '\0';	//pas sur du -1 flm de reflaichir
	if (str)
		free(str);
	return (res);
}

char	*search_cmd(const char *src, t_set *set)
{
	int		quot;
	int		exit;
	char	*res;

	set->y = 0;
	quot = 0;
	set->word_tmp = ft_strdup("");
	while ((ft_iswhite(src[set->y]) == 1 && quot == 0) || (src[set->y] == '\"' && src[set->y + 1] == '\"')
		|| (src[set->y] == '\'' && src[set->y + 1] == '\''))
	{
		if ((src[set->y] == '\"' && src[set->y + 1] == '\"') || (src[set->y] == '\'' && src[set->y + 1] == '\''))
		{
			quot = 1;
			set->y++;
		}
		set->y++;
	}
	//printf("white src[y] = |%c|\n",src[set->y]);
	exit = 0;
	while (exit == 0)
	{
		if (src[set->y] == '\'')
			exit = search_quotes(src, set, '\'');
		else if (src[set->y] == '\"')
			exit = search_quotes(src, set, '\"');
		else if (ft_iswhite(src[set->y]) != 1)
		{
			while (src[set->y] && ft_iswhite(src[set->y]) != 1 && src[set->y] != '\'' && src[set->y] != '\"')
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
		if ((ft_iswhite(src[set->y]) == 1 || !src[set->y]) && exit == 0)
			exit = 1;
	}
	if (exit == -1)
		set->err_quote = 1;
	/* TODO if exit == -1 = {problème de quote} */
	//printf("cmd  = |%s|\nexit = %d\n", set->word_tmp, exit);
	res = ft_strdup(set->word_tmp);
	free(set->word_tmp);
	return (res);
}

int		clean(char *src, t_set *set)
{
	char	*cpy;

	cpy = redirection(src, set);
	//printf("cpy_redirection = |%s|\n", cpy);
	cpy = search_dolars(cpy, set); // attention pas oublier de free cpy dans crt file
	//printf("cpy_dolars = |%s|\n", cpy);
	//printf("\n\n\n\n-------------------------------------------\nStart to clean cmd : |%s|\n", src);
	set->cmd = search_cmd(cpy, set);
	//printf("set-cmd = {%s}\nsrc = {%s}\n", set->cmd, src);
	set->arg = search_arg(cpy, set);

	return (0);
}

int	error_list(int a, t_set *set)
{
	if (a == 1)
		ft_putstr_fd("minishell: syntax error near unexpected token `;'\n",1);
	if (a == 2)
		ft_putstr_fd("minishell: syntax error near unexpected token `;;'\n",1);
	set->exit_val = 2;
	return (-1);
}

int 	first_semicon(const char *str)
{
	int	i;
	int	e;

	e = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ';')
		{
			if (str[i] == ';' && str[i + 1] == ';')
				return (2);
			if (str[i] == ';' && e == 0)
				return (1);
			else
				return (0);
		}
		if (ft_iswhite(str[i]) == 0)
			e++;
		i++;
	}
	return (0);
}

int		check_list(const char *str, t_set *set)
{
	int	i;
	int	e;

	e = first_semicon(str);
	if (e != 0)
	{
		return (error_list(e, set));
	}
	e = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ';' && str[i + 1] == ';')
			return (error_list(2, set));
		if (str[i] == ';')
		{
			i++;
			e = 0;
			while (str[i] != ';' && str[i])
			{
				if (ft_iswhite(str[i]) == 0)
					e++;
				i++;
			}
			if (e == 0 && str[i])
				return (error_list(1, set));
		}
		i++;
	}
	return (0);
}

void	treat_cmd(t_set *set)
{
	char **list;
	int i;
	int e;

	i = 0;
	if (check_list(set->str, set) == 0)
	{
		list = split_semicolon(set->str, set);
		while (list[i])
		{
			e = 0;
			set->err_quote = 0;
			clean(list[i], set);
			start_cmd(set);
			free(set->cmd);
			while (set->arg[e])
			{
				//printf("\n\n\nset->arg[e] = %s\n\n\n", set->arg[e]);
				free(set->arg[e]);
				e++;
			}
			free(set->arg);
			i++;
		}
		e = 0;
		while (list[e])
		{
			free(list[e]);
			e++;
		}
		free(list);
	}
}
