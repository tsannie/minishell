/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:13:23 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/09 15:03:16 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int				ncmpel(char *s1, char *s2)
{
	int			i;

	i = 0;
	while ((s2[i] || s1[i]) && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int				ft_unsetenv(t_set *set, int j)
{
	int			i;

	i = 0;
	while (set->envp[i] != NULL)
	{
		//printf("[%s][%s][%d]\n", set->arg[j], set->envp[i],ncmpel(set->arg[j], set->envp[i]));
		if (ncmpel(set->arg[j], set->envp[i]) == 0)
		{
			while (set->envp[i] != NULL)
			{
				set->envp[i] = set->envp[i+1];
				i++;
			}
			set->envp[i] = NULL;
			return (0);
		}
		i++;
	}
	return (0);
}

int				ft_unsethideenv(t_set *set, int j)
{
	int			i;

	i = 0;
	while (set->hide_envp[i] != NULL)
	{
		//printf("[%s][%s][%d]\n", set->arg[j], set->hide_envp[i],ncmpel(set->arg[j], set->hide_envp[i]));
		if (ncmpel(set->arg[j], set->hide_envp[i]) == 0)
		{
			while (set->hide_envp[i] != NULL)
			{
				set->hide_envp[i] = set->hide_envp[i+1];
				i++;
			}
			set->hide_envp[i] = NULL;
			return (0);
		}
		i++;
	}
	return (0);
}

int				ft_unset(t_set *set)
{
    int			j;

	j = 0;
	while (set->arg[j])
	{
		 if (checkenvp(set->arg[j]) == 1)
        {
            printf("minishell: unset: `%s': not a valid identifier\n", set->arg[j]);
            set->exit_val = 1; // a retirer 
            return (1);
        }
		ft_unsethideenv(set, j);
		ft_unsetenv(set, j);
		j++;
	}
    return (0);
}