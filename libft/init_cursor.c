/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 13:24:23 by sanam             #+#    #+#             */
/*   Updated: 2020/06/06 00:36:35 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_cursor(t_term *config, t_line *data)
{
	get_window_size(config);
	get_cursor_pos(config, data);
}

void	get_cursor_pos(t_term *config, t_line *data)
{
	size_t	temp;

	data->line_size = ft_strlen(data->line);
	temp = data->cursor_pos;
	data->cursor[X] = 0;
	while (temp >= config->width)
	{
		temp -= config->width;
		data->cursor[X]++;
	}
	data->cursor[Y] = temp;
}
