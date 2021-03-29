/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_correct2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:16:36 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/23 16:26:34 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int		first_pipe(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' && str[i])
		i++;
	if (str[i] == '|' && str[i + 1] == '|')
		return (11);
	if (str[i] == '|')
		return (10);
	return (0);
}

int		first_part(const char *str, t_set *set)
{
	int	e;

	if ((e = first_pipe(str)) != 0)
		return (error_list(e, set));
	if ((e = first_semicon(str)) != 0)
		return (error_list(e, set));
	return (0);
}

int		after_pipe(const char *str, int i)
{
	int	e;

	e = i;
	while (str[e] == '|')
		e++;
	while (str[e] == ' ' && str[e])
		e++;
	if (str[e] == ';' && str[e + 1] == ';')
		return (2);
	if (str[e] == ';')
		return (1);
	if ((!str[e] || str[e] == '|') && str[i + 1] == '|')
		return (11);
	if (!str[e] || str[e] == '|')
		return (10);
	return (0);
}

int		nb_pipe(const char *str, int i)
{
	int	nb;

	nb = 0;
	while (str[i] == '|' && str[i])
	{
		i++;
		nb++;
	}
	if (nb >= 4)
		return (11);
	if (nb >= 2)
		return (10);
	return (0);
}

int		before_pipe(const char *str, int i)
{
	int	e;

	e = i;
	e--;
	while (str[e] == ' ' && e >= 0)
		e--;
	if (str[e] == ';' && str[i + 1] == '|')
		return (11);
	if (str[e] == ';')
		return (10);
	return (0);
}

int		check_pipe(const char *str, int i)
{
	int e;

	if ((e = before_pipe(str, i)) != 0)
		return (e);
	if ((e = nb_pipe(str, i)) != 0)
		return (e);
	if ((e = after_pipe(str, i)) != 0)
		return (e);
	return (0);
}
