/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 12:30:59 by sanam             #+#    #+#             */
/*   Updated: 2020/06/07 22:27:07 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	get_window_size(t_term *config)
{
	ioctl(0, TIOCGWINSZ, &config->window_size);
	config->width = config->window_size.ws_col;
	config->height = config->window_size.ws_row;
}

int		init_terminal(t_term *config, t_line *data, char *prompt)
{
	struct termios	change;

	tgetent(NULL, getenv("TERM"));
	tcgetattr(0, &change);
	change.c_lflag &= ~(ECHO | ICANON);
	change.c_cc[VMIN] = 1;
	change.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &change);
	get_window_size(config);
	ft_tputs("sc");
	data->config = config;
	init_line(data, prompt);
	return (0);
}

void	init_line(t_line *data, char *prompt)
{
	ft_bzero(data->buf, 6);
	data->line = ft_strdup(prompt);
	data->prompt = prompt;
	data->prompt_size = ft_strlen(prompt);
	data->line_size = data->prompt_size;
	data->cursor_pos = data->prompt_size;
	if (data->sigint_count == 1)
	{
		data->sigint_count = 0;
		return ;
	}
	ft_putstr_fd("\033[36m\033[3m\033[01m", 1);
	ft_putstr_fd(prompt, 1);
	ft_putstr_fd("\033[0m", 1);
}

void	restore_term(void)
{
	struct termios	change;

	tgetent(NULL, getenv("TERM"));
	tcgetattr(0, &change);
	change.c_lflag |= ICANON;
	change.c_lflag |= ECHO;
	tcsetattr(0, TCSANOW, &change);
}
