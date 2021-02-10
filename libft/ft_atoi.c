/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:49:24 by tsannie           #+#    #+#             */
/*   Updated: 2020/10/11 10:28:56 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	char	*src;
	int		res;
	int		i;
	int		neg;

	res = 0;
	i = 0;
	src = (char *)str;
	while (src[i] == ' ' || src[i] == '\t' || src[i] == '\v' || src[i] == '\r'
		|| src[i] == '\f' || src[i] == '\n')
		i++;
	neg = (src[i] == '-') ? 1 : 0;
	i = (src[i] == '-' || src[i] == '+') ? i + 1 : i;
	while (src[i] >= '0' && src[i] <= '9')
	{
		res = (res * 10) + (src[i] - '0');
		i++;
	}
	return ((neg == 1) ? -res : res);
}
