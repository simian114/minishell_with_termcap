/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoon <gmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:50:17 by gmoon             #+#    #+#             */
/*   Updated: 2020/06/07 22:52:06 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_prompt(void)
{
	char	*cwd;
	char	*curr;
	char	*prompt;

	cwd = getcwd(0, 1024);
	curr = ft_strrchr(cwd, '/') + 1;
	prompt = ft_strjoin(curr, " >> ");
	free(cwd);
	return (prompt);
	
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*envs;
	t_dlist *history;
	int		wstatus;
	char	*prompt;

	g_line = 0;
	wstatus = 0;
	init_shell(argc, argv, envp, &envs);
	signal(SIGQUIT, sigquit_handle);
	history = 0;
	while (1)
	{
		prompt = make_prompt();
		g_line = get_line_term(prompt, &history);
		wstatus = 0;
		signal(SIGINT, sigint_handle);
		signal(SIGQUIT, sigquit_handle);
		exec_line(g_line, envs, envp, &wstatus);
		free(prompt);
	}
}
