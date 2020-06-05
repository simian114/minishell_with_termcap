/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoon <gmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:50:17 by gmoon             #+#    #+#             */
/*   Updated: 2020/06/06 00:44:26 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*envs;
	t_dlist *history;
	char	*line;
	int		wstatus;

	wstatus = 0;
	g_core = getpid();
	if (!argc && argv)
		exit(1);
	print_art();
	signal(SIGINT, sigint_handle);
	signal(SIGQUIT, sigquit_handle);
	envs = make_envs(envp);
//	while ((get_line(&line)) || (wstatus = 0))
//		exec_line(line, envs, envp, &wstatus);
	line = 0;
	history = 0;
	while (1)
	{
		line = get_line_term("sanam >> ", &history);
		wstatus = 0;
		exec_line(line, envs, envp, &wstatus);
	}
	free(line);
	ft_lstclear(&envs, del);
}
