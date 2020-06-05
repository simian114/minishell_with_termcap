/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_splited.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanam <sanam@studenr.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:31:08 by sanam             #+#    #+#             */
/*   Updated: 2020/04/30 20:41:26 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_free_splited(char **freed)
{
	int			i;

	i = 0;
	while (freed[i])
		free(freed[i++]);
	free(freed[i]);
	free(freed);
}
