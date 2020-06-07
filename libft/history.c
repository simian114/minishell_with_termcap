/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 15:38:24 by sanam             #+#    #+#             */
/*   Updated: 2020/06/08 01:41:30 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		delete_down(t_line *data)
{
	while (data->cursor[X]++ < data->line_size / (int)data->config->width)
		ft_tputs("do");
	while (data->cursor[X]-- > 1)
	{
		ft_tputs("dl");
		ft_tputs("up");
	}
}

t_dlist		*search_up(t_line *data, t_dlist *history)
{
	if (history == 0)
		return (history);
	else
	{
		if (data->line_size > data->config->width)
			delete_down(data);
		free(data->line);
		data->line = ft_strjoin(data->prompt, history->content);
		ft_tputs("dl");
		ft_putstr_fd("\033[36m\033[3m\033[01m", 1);
		ft_putstr_fd(data->prompt, 1);
		ft_putstr_fd("\033[0m", 1);
		ft_putstr_fd(history->content, 1);
		data->cursor_pos = ft_strlen(data->line);
		if (history->next)
			history = history->next;
		return (history);
	}
}

t_dlist		*search_down(t_line *data, t_dlist *history)
{
	if (ft_dlstsize(history) == 0 || history->prev == 0)
		return (history);
	else
	{
		history = history->prev;
		if (data->line_size > data->config->width)
			delete_down(data);
		free(data->line);
		data->line = ft_strjoin(data->prompt, history->content);
		ft_tputs("dl");
		ft_putstr_fd("\033[36m\033[3m\033[01m", 1);
		ft_putstr_fd(data->prompt, 1);
		ft_putstr_fd("\033[0m", 1);
		ft_putstr_fd(history->content, 1);
		data->cursor_pos = ft_strlen(data->line);
		return (history);
	}
}

t_dlist		*search_history(t_line *data, t_dlist *history, char arrow)
{
	if (arrow == UP)
		return (search_up(data, history));
	else
		return (search_down(data, history));
}
