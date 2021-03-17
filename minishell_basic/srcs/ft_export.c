/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phbarrad <phbarrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:27:05 by phbarrad          #+#    #+#             */
/*   Updated: 2021/03/17 10:16:34 by phbarrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int				checkenvp(char *str)
{
	int			i;
	int			avn;

	i = 0;
	avn = 0;
	if (str[i] == '=')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (str[i] >= 48 && str[i] <= 59 && avn == 0)
			return (1);
		if (((str[i] < 48) || (str[i] >= 58 && str[i] <= 64) || (str[i] >= 123)
		|| (str[i] >= 91 && str[i] <= 96) )  && (str[i] != '_'))
		{
			return (1);
		}
		else
			avn = 1;
		i++;
	}
	return (0);
}

char			*recup_new(char *str, int x)
{
	char		*nstr;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (!(nstr = malloc(sizeof(char) * (ft_strlen(str) + 4))))
		return (0);
	while (j < x)
	{
		nstr[j] = str[j];
		j++;
	}
	nstr[j] = '\"';
	while (str[j])
	{
		nstr[j + 1] = str[j];
		j++;
	}
	nstr[j + 1] = '\"';
	nstr[j + 2] = '\0';
	return (nstr);

}

int				ft_hideenv(char *str, t_set *set)
{
	int			i;
	int			act;
	int			r;
	int			j;

	act = 0;
	i = 0;
	r = 0;
	j = 0;
   // while(str[i] != '=' && str[i])
	//	i++;
	// printf("[%d][%d]\n",i, (int)ft_strlen(str));
	//if (i != (int)ft_strlen(str))
	   // str = recup_new(str, i + 1);
	i = 0;
	while (set->hide_envp[i] != NULL)
	{
		if(ncmpel(str, set->hide_envp[i]) == 0)
		{
			free(set->hide_envp[i]);
			set->hide_envp[i] = ft_strdup(str);
			act = 1;
		}
		i++;
	}
	//printf("hide = [%s]\n", str);
	if (act == 0)
	{
		set->hide_envp = addword(set->hide_envp,i + 1, set, str);
		//set->hide_envp = addword(set->hide_envp, i + 2, set, NULL);
	}
/*
		free(set->hide_envp[i]);
		set->hide_envp[i] = ft_strdup(str);
	}
	set->hide_envp[i + 1] = malloc(sizeof(char) * 1);
	set->hide_envp[i + 1] = NULL; */

	//printf("\n\n\n\n\n");
	//set->hide_envp[12 + 1] = malloc(sizeof(char) * 1);
	//set->hide_envp[12 + 1] = NULL;
 	i = 0;
	/* while (set->hide_envp[i] != NULL)
	{
		printf("{%s}\n", set->hide_envp[i]);
		i++;
	}*/

	return (0);
}

int 			ft_modenv(char *str, t_set *set)
{
	int			i;
	int			act;
	int			r;
	int			j;

	act = 0;
	i = 0;
	r = 0;
	j = 0;
   // while(str[i] != '=' && str[i])
	 //   i++;
	// printf("[%d][%d]\n",i, (int)ft_strlen(str));
	//if (i != (int)ft_strlen(str))
	 //   str = recup_new(str, i + 1);
	//set->envp = addword(set->envp, i, set, str)
	i = 0;
	while (set->envp[i] != NULL)
	{
		if(ncmpel(str, set->envp[i]) == 0)
		{
			free(set->envp[i]);
			set->envp[i] = ft_strdup(str);
			act = 1;
		}
		i++;
	}
	if (act == 0)
	{
		set->envp = addword(set->envp, i + 1, set, str);
		set->envp[i + 1] = NULL;
		//set->hide_envp = addword(set->hide_envp, i + 2, set, NULL);
	}
/* 		free(set->envp[i]);
		set->envp[i] = ft_strdup(str);
	}
	set->envp[i + 1] = malloc(sizeof(char) * 1);
	set->envp[i + 1] = NULL; */
	return (0);
}

int				there_is_slash(char *word)
{
	int			i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '\\')
			return (1);
		i++;
	}
	return (0);
}

void			double_slash(t_set *set)
{
	int			i;
	int			e;
	char		*str;

	i = 0;
	while (set->arg[i])
	{
		//printf("arg = |%s|\n", set->arg[i]);
		if (there_is_slash(set->arg[i]) == 1)
		{
			e = 0;
			str = ft_strdup("");
			while (set->arg[i][e])
			{
				if (set->arg[i][e] == '\\')
					str = add_letter(str, '\\');
				str = add_letter(str, set->arg[i][e]);
				e++;
			}
			free(set->arg[i]);
			set->arg[i] = ft_strdup(str);
			free(str);
		}
		i++;
	}
}

int				ft_export(t_set *set)
{
	int			i;
	int			j;
	int			egl;

	egl = 0;
	j = -1;
	i = -1;

/*	  printf("str = [%s]\n", set->str);
	int r = -1;
	while (set->arg[++r])
		printf("arg = [%s]\n", set->arg[r]);
	printf("arg = [%s]\n", set->arg[r]);
	*/
	//= exp & env
	// -= exp
	//printf("salutation\n");
	double_slash(set);
	//print_args(set->arg);
	if (ft_streql(set->cmd, "export") != 1)
	{
		ft_putstr_not_found(set->cmd, set);
		//printf("pq\n");
		return (1);
	}
	//print_args(set->arg);
	//print_args(set->arg);
	if (set->arg[0] == NULL)
		ft_disp_export(set);
	else
	{
		while (set->arg[++i])
		{
			//printf("arg = [%s]\n", set->arg[i]);
			while (set->arg[i][++j])
			{
				if (set->arg[i][j] == '=')
					egl = 1;
			}
			if (checkenvp(set->arg[i]) == 1)
			{
				printf("minishell: export: `%s': not a valid identifier\n", set->arg[i]);
				set->exit_val = 1; // a retirer
			}
			else if (egl == 1)
			{
				ft_hideenv(set->arg[i], set);
				ft_modenv(set->arg[i], set);
		 	}
			else
				ft_hideenv(set->arg[i], set);
			egl = 0;
			j = -1;
		}
	}

	//printf("\n\n\n");
	//print_args(set->hide_envp);
	ft_sort_dbtab(set);

	return (0);
}
