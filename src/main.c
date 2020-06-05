/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoon <gmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:50:17 by gmoon             #+#    #+#             */
/*   Updated: 2020/06/06 01:35:15 by sanam            ###   ########.fr       */
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
	prompt = ft_strjoin("\033[36m\033[3m\033[01m", curr);
	prompt = ft_strjoin_s1free(prompt, " >> ");
	prompt = ft_strjoin_s1free(prompt, "\033[0m");
	free(cwd);
	return (prompt);
	
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*envs;
	t_dlist *history;
	char	*line;
	int		wstatus;
	char	*prompt;

	wstatus = 0;
	g_core = getpid();
	init_shell(argc, argv, envp, &envs);
	signal(SIGINT, sigint_handle);
	signal(SIGQUIT, sigquit_handle);
	history = 0;
	while (1)
	{
		prompt = make_prompt();
		line = get_line_term(prompt, &history);
		wstatus = 0;
		exec_line(line, envs, envp, &wstatus);
		free(prompt);
	}
}
