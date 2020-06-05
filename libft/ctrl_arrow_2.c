/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_arrow_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 20:34:52 by sanam             #+#    #+#             */
/*   Updated: 2020/06/06 00:37:32 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	up_line(t_line *data)
{
	ft_tputs("up");
	data->cursor_pos -= data->config->width;
	if (data->cursor_pos < data->prompt_size)
		while (data->cursor_pos++ != data->prompt_size)
			ft_tputs("nd");
}

void	down_last(t_line *data)
{
	size_t	temp;

	temp = data->line_size % data->config->width;
	if (temp >= data->cursor[Y])
	{
		while (data->cursor[Y]--)
			ft_tputs("nd");
		data->cursor_pos += data->config->width;
	}
	else
	{
		data->cursor_pos += data->config->width - data->cursor[Y];
		data->cursor_pos += temp;
		while (temp-- > 0)
			ft_tputs("nd");
	}
}

void	down_line(t_line *data)
{
	ft_tputs("do");
	if (data->line_size / data->config->width == data->cursor[X] + 1)
		down_last(data);
	else
	{
		ft_putendl_fd("qwe", 1);
		while (data->cursor[Y]--)
			ft_tputs("nd");
		data->cursor_pos += data->config->width;
	}
}
