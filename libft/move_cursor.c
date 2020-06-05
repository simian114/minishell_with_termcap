/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 00:27:36 by sanam             #+#    #+#             */
/*   Updated: 2020/06/06 00:37:42 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		left_arrow(t_line *data)
{
	int		i;

	data->cursor_pos--;
	if (data->cursor[X] == 0)
	{
		ft_tputs("le");
		return ;
	}
	if (data->cursor[X] > 0)
	{
		if ((int)data->cursor[Y] != 0)
		{
			ft_tputs("le");
			return ;
		}
		else
		{
			i = -1;
			while (++i < (int)data->config->width + 1)
				ft_tputs("nd");
			ft_tputs("up");
			return ;
		}
	}
}

void		right_arrow(t_line *data)
{
	if (data->cursor_pos >= ft_strlen(data->line))
		return ;
	if (data->cursor[Y] >= data->config->width - 1)
	{
		ft_tputs("do");
		data->cursor_pos++;
		return ;
	}
	data->cursor_pos++;
	ft_tputs("nd");
}

void		move_home(t_line *data)
{
	if (data->cursor_pos == data->prompt_size)
		return ;
	while (data->cursor[X]-- > 0)
		ft_tputs("up");
	if (data->cursor[Y] > data->prompt_size)
		while (data->cursor[Y]-- > data->prompt_size)
			ft_tputs("le");
	else
		while (data->cursor[Y]++ < data->prompt_size)
			ft_tputs("nd");
	data->cursor_pos = data->prompt_size;
}

void		move_end(t_line *data)
{
	int			flag;
	size_t		i;

	i = 0;
	flag = 0;
	if (data->cursor_pos == data->line_size)
		return ;
	else if (data->line_size < data->config->width && data->cursor[X] == 0)
		while (data->cursor[Y]++ < data->line_size)
			ft_tputs("nd");
	else
	{
		while (data->cursor[X]++ < data->line_size / data->config->width
				&& (++flag))
			ft_tputs("do");
		if (flag == 0)
			while (data->cursor[Y]++ < data->line_size % data->config->width)
				ft_tputs("nd");
		else
			while (i++ < data->line_size % data->config->width)
				ft_tputs("nd");
	}
	data->cursor_pos = data->line_size;
}

void			move_cursor(t_line *data)
{
	if (data->buf[2] == HOME)
		move_home(data);
	else if (data->buf[2] == END)
		move_end(data);
	else if (data->buf[2] == LEFT)
	{
		if (!(data->cursor_pos > data->prompt_size))
			return ;
		else
			left_arrow(data);
	}
	else
		right_arrow(data);
}
