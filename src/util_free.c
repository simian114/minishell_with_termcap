/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoon <gmoon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 23:13:15 by gmoon             #+#    #+#             */
/*   Updated: 2020/06/06 13:23:32 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_char(char ***str)
{
	char **str_adr;

	str_adr = *str;
	while (**str)
	{
		free(**str);
		(*str)++;
	}
	free(str_adr);
}

void	free_triple_char(char ****cmds)
{
	char ***triple_adr;
	char **double_adr;

	triple_adr = *cmds;
	while (**cmds)
	{
		double_adr = **cmds;
		while (***cmds)
		{
			free(***cmds);
			(**cmds)++;
		}
		(*cmds)++;
		free(double_adr);
	}
	free(triple_adr);
}

void	del(void *content)
{
	t_env *temp;

	temp = (t_env *)content;
	free(temp->key);
	free(temp->value);
	free(temp);
}

void	del_double(void *content)
{
	char	*temp;

	temp = (char *)content;
	free(temp);
}
