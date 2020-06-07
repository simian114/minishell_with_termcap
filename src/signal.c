/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoon <gmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 02:19:55 by gmoon             #+#    #+#             */
/*   Updated: 2020/06/07 22:28:28 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sigint_handle(int signo)
{
	int		t;

	t = signo;
	signo = t;
	ft_putendl_fd("", 1);
	signal(SIGINT, SIG_DFL);
}

void		sigquit_handle(int signo)
{
	int		t;
	char	**temp;

	t = signo;
	signo = t;
	signal(SIGQUIT, SIG_DFL);
	temp = ft_split(g_line, ' ');
	ft_putstr_fd("[1]	", 2);
	ft_putnbr_fd(getpid(), 2);
	ft_putstr_fd(" quit	", 2);
	ft_putendl_fd(temp[0], 2);
	ft_free_splited(temp);
}
