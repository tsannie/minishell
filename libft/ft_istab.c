/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_istab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:35:09 by tsannie           #+#    #+#             */
/*   Updated: 2021/03/19 12:35:54 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_istab(char a)
{
	if (a == ' ' || a == '\t')
		return (1);
	return (0);
}