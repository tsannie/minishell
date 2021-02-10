/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsannie <tsannie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:46:19 by phbarrad          #+#    #+#             */
/*   Updated: 2021/02/10 12:23:10 by tsannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

void int_handler(int sig)
{
    signal(sig, SIG_IGN);
}

void disp_prompt(void)
{
    ft_putstr("{MINISHELL}$> ");
}

int main(int ac, char **av, char **envp)
{
    while (1)
    {
        disp_prompt();
        signal(SIGINT, int_handler);
    }
    return (0);
}
