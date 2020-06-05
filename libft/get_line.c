/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:46:25 by sanam             #+#    #+#             */
/*   Updated: 2020/06/06 00:45:17 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	parse_input(t_line *data, t_dlist **history, t_dlist **temp)
{
	if (data->buf[0] == 4)
	{
		if (ft_strlen(data->line) == data->prompt_size)
			exit(0);
	}
	else if (data->buf[0] == ESC && data->buf[5] != 0)
		ctrl_arrow(data, data->buf[5]);
	else if (ft_isprint(data->buf[0]) && data->buf[1] == 0)
		insert(data);
	else if (data->buf[0] == DEL && data->cursor_pos > data->prompt_size)
		delete(data);
	else if (data->buf[0] == ESC &&
			(data->buf[2] == UP || data->buf[2] == DOWN))
		*temp = search_history(data, *temp, data->buf[2]);
	else if (data->buf[0] == ESC)
		move_cursor(data);
	ft_bzero(data->buf, 6);
	if (ft_dlstsize(*history) != 0 && temp == 0)
		*temp = *history;
}

char	*get_line_term(char *prompt, t_dlist **history)
{
	t_term			config;
	t_line			data;
	char			*ret;
	t_dlist			*temp;

	temp = *history;
	init_terminal(&config, &data, prompt);
	while ((read(0, &data.buf, 6)) && data.buf[0] != RET)
	{
		init_cursor(&config, &data);
		parse_input(&data, history, &temp);
	}
	ft_putendl_fd("", 1);
	ret = ft_strdup(&data.line[data.prompt_size]);
	free(data.line);
	if (ft_strlen(ret) > 0)
		ft_dlstadd_front(history, ft_dlstnew(ft_strdup(ret)));
	return (ret);
}

//int		main(void)
//{
//	char	*line;
//	t_dlist	*history;
//
//	history = 0;
//	line = NULL;
//	while ((line = get_line_term("sanam >> ", &history)))
//	{
//		if (ft_strlen(line) == 0)
//			free(line);
//		else
//		{
//			ft_putendl_fd("====================", 1);
//			ft_putendl_fd(line, 1);
//			ft_putendl_fd("====================", 1);
//			free(line);
//		}
//	}
//}
//
