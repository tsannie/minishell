/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 08:17:41 by tsannie           #+#    #+#             */
/*   Updated: 2021/02/17 16:57:29 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

char	**addword(char **res, int nb_word, t_set *set, char *word)
{
	char	**new;
	int		i;

	if (!(new = malloc(sizeof(char*) * (nb_word + 1))))
		return (NULL);
	i = 0;
	while (res[i])
	{
			//printf("set.cmd = {%s}\n", set->cmd);
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

char	**search_arg(char *str, t_set *set)
{
	//printf("\nstart parcing arg :\n");
	//printf("y = %d\nstr[y] = {%c}\nstr = {%s}\n", set->y, str[set->y], &str[set->y]);
	char	**res;
	char	*word;
	int 	exit;
	int		nb_word;

	nb_word = 0;
	exit = 2;
	while (ft_iswhite(str[set->y]) == 1 && str[set->y])
		set->y++;
	if (!(res = malloc(sizeof(char*) * 1)))
		return (NULL);
	res[0] = 0;
	while(str[set->y])
	{
		exit = 0;
		word = ft_strdup("");
		while (exit == 0)
		{
			if (str[set->y] == '\'')
			{
				set->y++;
				while (str[set->y] && str[set->y] != '\'')
				{
					word = add_letter(word, str[set->y]);
					set->y++;
				}
				if (str[set->y] != '\'')
					exit = -1;
				set->y++;
			}
			else if (str[set->y] == '\"')
			{
				set->y++;
				while (str[set->y] && str[set->y] != '\"')
				{
					if (str[set->y] == '\\' && str[set->y + 1] == '\"')
					{
						word = add_letter(word, str[set->y + 1]);
						set->y = set->y + 2;
					}
					else
					{
						word = add_letter(word, str[set->y]);
						set->y++;
					}
				}
				if (str[set->y] != '\"')
					exit = -1;
				set->y++;
			}
			else if (ft_iswhite(str[set->y]) != 1 && str[set->y])
			{
				while (str[set->y] && ft_iswhite(str[set->y]) != 1
					&& str[set->y] != '\'' && str[set->y] != '\"')
				{
					if ((str[set->y] == '\\' && str[set->y + 1]))
					{
						word = add_letter(word, str[set->y + 1]);
						set->y = set->y + 2;
					}
					else
					{
						word = add_letter(word, str[set->y]);
						set->y++;
					}
				}
			}
			if ((ft_iswhite(str[set->y]) == 1 || !str[set->y]) && exit == 0)
				exit = 1;
		}
		while (ft_iswhite(str[set->y]) == 1 && str[set->y])
			set->y++;
		if (!str[set->y] && exit == 0)
			exit = 1;
		nb_word++;
		res = addword(res, nb_word, set, word);
		//print_args(res);
		//printf("\n\n");
		free(word);
	}
	//print_args(res);
	if (exit == -1)
		set->err_quote = 1;
	//printf("exit = %d\n", exit);		// if exit == -1 error quote
	return (res);
}
