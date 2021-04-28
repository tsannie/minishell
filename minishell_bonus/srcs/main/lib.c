/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:30:07 by phbarrad          #+#    #+#             */
/*   Updated: 2021/04/28 14:52:25 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minish_bonus.h"

char					*ft_strdupbc(const char *s1)
{
	char				*res;
	int					len;
	int					i;

	len = 0;
	while (s1[len])
		len++;
	while (s1[len] != '/' && len > 0)
		len--;
	i = 0;
	if (!(res = malloc(sizeof(char) * (len + 2))))
		return (NULL);
	while (s1[i] && i <= len)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

unsigned long long		ft_atoill(const char *str)
{
	int					i;
	unsigned long long	result;

	i = 0;
	result = 0;
	while (str[i] == 32 || str[i] == '\t' || str[i] == '\n' ||
	str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result);
}

char					**ft_strdup_tabl(char **envp)
{
	char				**hide_envp;
	int					y;
	int					len;

	len = 0;
	y = 0;
	while (envp[len] != NULL)
		len++;
	if (!(hide_envp = malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (envp[y])
	{
		hide_envp[y] = ft_strdup(envp[y]);
		y++;
	}
	hide_envp[y] = NULL;
	return (hide_envp);
}

char					*joinf(char *s1, char *s2, char *s3, char *s4)
{
	char				*res;
	int					globalsize;
	int					i;
	int					e;

	globalsize = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + ft_strlen(s4);
	if (!(res = malloc(sizeof(char) * globalsize + 1)))
		return (NULL);
	i = 0;
	e = 0;
	while (s1[i])
		res[i++] = s1[e++];
	e = 0;
	while (s2[e])
		res[i++] = s2[e++];
	e = 0;
	while (s3[e])
		res[i++] = s3[e++];
	e = 0;
	while (s4[e])
		res[i++] = s4[e++];
	res[i] = '\0';
	return (res);
}

int						ncmpelp(char *s1, char *s2)
{
	int					i;

	i = 0;
	while ((s2[i] || s1[i]) && s2[i] != '=' && s2[i] != '+')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
