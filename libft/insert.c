/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 12:25:23 by sanam             #+#    #+#             */
/*   Updated: 2020/06/06 00:37:11 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	add_last(t_line *data)
{
	ft_putchar_fd(data->buf[0], 1);
	if (data->cursor_pos % data->config->width == 0)
		ft_tputs("do");
}

static void	add_middle(t_line *data)
{
	size_t i;

	ft_tputs("sc");
	ft_putstr_fd(data->line + data->cursor_pos - 1, 1);
	ft_tputs("rc");
	if (data->cursor_pos % data->config->width == 0)
	{
		ft_tputs("do");
		i = data->config->width;
		while (i--)
			ft_tputs("le");
	}
	else
		ft_tputs("nd");
}

void		insert(t_line *data)
{
	data->line = realloc(data->line, (data->line_size + 2));
	ft_memset(data->line + data->line_size, 0, 2);
	ft_memmove(data->line + data->cursor_pos + 1,
			data->line + data->cursor_pos,
			ft_strlen(data->line + data->cursor_pos));
	data->line[data->cursor_pos] = data->buf[0];
	data->cursor_pos++;
	if (data->line_size == data->cursor_pos - 1)
		add_last(data);
	else
		add_middle(data);
}
