/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 07:41:05 by tsannie           #+#    #+#             */
/*   Updated: 2021/02/12 13:58:20 by phbarrad         ###   ########.fr       */
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

char	*search_cmd(char *src, t_set *set)
{
	char	*res;
	int		quot;
	int		exit;

	set->y = 0;
	quot = 0;
	res = ft_strdup("");
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
		{
			set->y++;
			while (src[set->y] && src[set->y] != '\'')
			{
				res = add_letter(res, src[set->y]);
				set->y++;
			}
			if (src[set->y] != '\'')
				exit = -1;
			set->y++;
		}
		else if (src[set->y] == '\"')
		{
			set->y++;
			while (src[set->y] && src[set->y] != '\"')
			{
				res = add_letter(res, src[set->y]);
				set->y++;
			}
			if (src[set->y] != '\"')
				exit = -1;
			set->y++;
		}
		else if (ft_iswhite(src[set->y]) != 1)
		{
			while (src[set->y] && ft_iswhite(src[set->y]) != 1 && src[set->y] != '\'' && src[set->y] != '\"')
			{
				res = add_letter(res, src[set->y]);
				set->y++;
			}
		}
		if ((ft_iswhite(src[set->y]) == 1 || !src[set->y]) && exit == 0)
			exit = 1;
	}
	/* TODO if exit == -1 = {problème de quote} */
	printf("cmd  = |%s|\nexit = %d\n", res, exit);
	return (res);
}

int		clean(char *src, t_set *set)
{
	printf("\n\n\n\n-------------------------------------------\nStart to clean cmd : |%s|\n", src);
	set->cmd = search_cmd(src, set);
	set->arg = search_arg(src, set);

	return (0);
}

void	treat_cmd(t_set *set, char **envp)
{
	char **list;
	int i;

	i = 0;
	list = ft_split(set->str, ';');
	while (list[i])
	{
		clean(list[i], set);
		start_cmd(envp, set);
		i++;
	}
}
