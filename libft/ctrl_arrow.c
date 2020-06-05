/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_arrow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 18:11:17 by sanam             #+#    #+#             */
/*   Updated: 2020/06/06 00:37:27 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	next_word(t_line *data)
{
	size_t	temp;
	char	*space;

	if (!(space = ft_strchr(&data->line[data->cursor_pos], ' ')))
		return ;
	while (*space == ' ')
		space++;
	if (space == NULL)
		return ;
	if (data->cursor[X] < (space - data->line) / data->config->width)
	{
		while (data->cursor[X]++ < (space - data->line) / data->config->width)
			ft_tputs("do");
		temp = (space - data->line) % data->config->width;
		while (temp--)
			ft_tputs("nd");
		data->cursor_pos = (size_t)(space - data->line);
		return ;
	}
	while ((int)data->cursor_pos++ < (space - data->line))
		ft_tputs("nd");
	data->cursor_pos--;
}

void	before_word(t_line *data)
{
	size_t	curr;
	char	**splited;

	curr = data->cursor_pos;
	while (data->line[curr - 1] == ' ')
		if (--curr <= data->prompt_size)
			return ;
	splited = ft_split(&data->line[data->prompt_size], ' ');
	if (*splited == 0 || ft_split_count(splited) == 1)
	{
		while (data->line[data->cursor_pos] - 1 != ' ')
			if (!(data->cursor_pos > data->prompt_size))
				left_arrow(data);
		ft_free_splited(splited);
		return ;
	}
	else
	{
		ft_putstr_fd("here", 1);
	}
	return ;
}

void	ctrl_arrow(t_line *data, char arrow)
{
	if (arrow == RIGHT)
		next_word(data);
	else if (arrow == UP)
	{
		if (data->cursor[X] < 1)
			return ;
		up_line(data);
	}
	else
	{
		if (data->cursor[X] == data->line_size / data->config->width)
			return ;
		down_line(data);
	}
}
