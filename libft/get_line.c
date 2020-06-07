/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:46:25 by sanam             #+#    #+#             */
/*   Updated: 2020/06/07 22:27:01 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	parse_input(t_line *data, t_dlist **history, t_dlist **temp)
{
	if (data->buf[0] == 4)
	{
		data->buf[0] = -1;
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
	char			*ret;
	t_dlist			*temp;

	ft_memset(&g_data, 0, sizeof(t_line));
	g_data.sigint_count = 0;
	signal(SIGINT, sigint_getline);
	signal(SIGQUIT, SIG_IGN);
	temp = *history;
	init_terminal(&config, &g_data, prompt);
	while ((read(0, &g_data.buf, 6)) && g_data.buf[0] != RET)
	{
		init_cursor(&config, &g_data);
		parse_input(&g_data, history, &temp);
	}
	ft_putendl_fd("", 1);
	ret = ft_strdup(&g_data.line[g_data.prompt_size]);
	free(g_data.line);
	if (ft_strlen(ret) > 0)
		ft_dlstadd_front(history, ft_dlstnew(ft_strdup(ret)));
	restore_term();
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
