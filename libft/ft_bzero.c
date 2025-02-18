/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:00:15 by nsaillez          #+#    #+#             */
/*   Updated: 2024/10/15 15:39:25 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *ptr, size_t n)
{
	char	*char_ptr;
	size_t	i;

	i = 0;
	char_ptr = (char *)ptr;
	while (i < n)
	{
		char_ptr[i] = 0;
		i++;
	}
}
