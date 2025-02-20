/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:47:40 by nsaillez          #+#    #+#             */
/*   Updated: 2025/02/20 16:48:04 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

int malloc_err()
{
	perror("malloc failed");
	return (-2);
}

int fork_err()
{
	perror("fork failed");
	return (-2);
}

int pipe_err()
{
	perror("pipe failed");
	return (-2);
}

int error_input(char *arg, int i, int n_cmd)
{
	int pipe_fd[2];

	if(pipe(pipe_fd) < 0)
		return(-1);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	i = i;
	n_cmd = n_cmd;
	ft_putstr_fd("Error - no such file or directory: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\n", 2);
	return (pipe_fd[0]);
}
