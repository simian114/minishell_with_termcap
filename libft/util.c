/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 14:30:29 by sanam             #+#    #+#             */
/*   Updated: 2020/06/06 00:36:03 by sanam            ###   ########.fr       */
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
