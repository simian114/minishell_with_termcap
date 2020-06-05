/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 01:34:27 by sanam             #+#    #+#             */
/*   Updated: 2020/06/06 01:36:35 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(int argc, char **argv, char **envp, t_list **envs)
{
	if (!argc && argv)
		exit(1);
	print_art();
	*envs = make_envs(envp);
}
