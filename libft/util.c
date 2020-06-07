/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 14:30:29 by sanam             #+#    #+#             */
/*   Updated: 2020/06/07 22:23:08 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

void	ft_tputs(char *cmd)
{
	tputs(tgetstr(cmd, NULL), 1, &ft_putchar);
}

void	sigint_getline(int signo)
{
	int		t;

	t = signo;
	signo = t;
	if (g_data.line == 0)
		return ;
	free(g_data.line);
	g_data.line = ft_strdup(g_data.prompt);
	g_data.line_size = g_data.prompt_size;
	g_data.cursor_pos = g_data.prompt_size;
	ft_bzero(g_data.buf, 6);
	ft_tputs("do");
	ft_putstr_fd("\033[36m\033[3m\033[01m", 1);
	ft_putstr_fd(g_data.prompt, 1);
	ft_putstr_fd("\033[0m", 1);
	g_data.sigint_count = 1;
}
