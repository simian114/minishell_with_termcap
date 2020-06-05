/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 16:08:32 by sanam             #+#    #+#             */
/*   Updated: 2020/06/06 00:37:16 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	delete_last(t_line *data)
{
	int		i;

	if (data->cursor[Y] == 0)
	{
		i = -1;
		while (i++ < (int)data->config->width)
			ft_tputs("nd");
		ft_tputs("up");
		ft_tputs("dc");
		return ;
	}
	ft_tputs("le");
	ft_tputs("dc");
}

static void	delete_middle_lowerline(t_line *data)
{
	size_t	temp;

	temp = data->cursor[X];
	ft_tputs("sc");
	while (temp < data->line_size / data->config->width)
	{
		ft_tputs("do");
		ft_tputs("dl");
		temp++;
	}
	ft_tputs("rc");
}

static void	delete_middle(t_line *data)
{
	int		i;

	delete_middle_lowerline(data);
	if (data->cursor[Y] == 0)
	{
		i = -1;
		ft_tputs("dl");
		while (i++ < (int)data->config->width)
			ft_tputs("nd");
		ft_tputs("up");
		ft_tputs("dc");
	}
	else
	{
		ft_tputs("le");
		ft_tputs("dc");
	}
	ft_tputs("sc");
	ft_putstr_fd(&data->line[data->cursor_pos], 1);
	ft_tputs("rc");
}

void		delete(t_line *data)
{
	data->line = realloc(data->line, data->line_size + 1);
	data->line[data->line_size] = 0;
	ft_memmove(data->line + data->cursor_pos - 1,
				data->line + data->cursor_pos,
				data->line_size - data->cursor_pos + 1);
	data->cursor_pos--;
	if (data->line_size == data->cursor_pos + 1)
		delete_last(data);
	else
		delete_middle(data);
}
