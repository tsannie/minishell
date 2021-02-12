/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 08:17:41 by tsannie           #+#    #+#             */
/*   Updated: 2021/02/12 14:32:49 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

void	print_args(char **str)
{
	int		i;

	i = 0;
	printf("\nargs_stock : \n");
	while (str[i])
	{
		printf("- Argument %d\t:\t|%s|\n", i, str[i]);
		i++;
	}
}

char	**addword(char **res, int nb_word)
{
	char	**new;
	int		i;

	if (!(new = malloc(sizeof(char*) * nb_word + 1)))
		return (NULL);
	i = 0;
	while (res[i])
	{
		new[i] = res[i];
		i++;
	}
	free(res);
	new[nb_word] = 0;
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
	while(str[set->y])
	{
		while (ft_iswhite(str[set->y]) == 1 && str[set->y])
			set->y++;
		if (!(str[set->y]))
			exit = 2;
		else
		{
			exit = 0;
			nb_word++;
			res = addword(res, nb_word);
			word = ft_strdup("");
		}
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
					word = add_letter(word, str[set->y]);
					set->y++;
				}
				if (str[set->y] != '\"')
					exit = -1;
				set->y++;
			}
			else if (ft_iswhite(str[set->y]) != 1 && str[set->y])
			{
				while (str[set->y] && ft_iswhite(str[set->y]) != 1 && str[set->y] != '\'' && str[set->y] != '\"')
				{
					word = add_letter(word, str[set->y]);
					set->y++;
				}
			}
			if ((ft_iswhite(str[set->y]) == 1 || !str[set->y]) && exit == 0)
				exit = 1;
		}
		res[nb_word - 1] = ft_strdup(word);
		free(word);
	}
	if (exit != 2)
	{
		print_args(res);
		printf("exit = %d\n", exit);		// if exit == -1 error quote
	}
	else
		printf("no arg\n");
	return (res);
}
