/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam <sanam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:38:03 by nam               #+#    #+#             */
/*   Updated: 2020/06/05 23:30:20 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist		*ft_dlstnew(void *content)
{
	t_dlist		*node;

	if (!(node = (t_dlist *)malloc(sizeof(t_dlist))))
		return (0);
	node->content = content;
	node->next = 0;
	node->prev = 0;
	return (node);
}
