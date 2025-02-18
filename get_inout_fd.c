/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inout_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:15:55 by nsaillez          #+#    #+#             */
/*   Updated: 2025/02/18 15:19:21 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void get_inout_fd(int *fd_io, int argc, char **argv)
{
	int i;

	i = 1;
	fd_io[0] = open(argv[i], O_RDONLY);
	while ((i + 1) < argc)
		i++;
	fd_io[1] = open(argv[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
}