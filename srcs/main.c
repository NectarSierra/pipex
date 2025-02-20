/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:58:12 by nsaillez          #+#    #+#             */
/*   Updated: 2025/02/20 14:02:39 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void close_waitall(int n_cmd, int *wait_list, int *fd_io)
{
	int status;
	int i;

	if (fd_io[0] > 0)
		close(fd_io[0]);
	close(fd_io[1]);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	i = 0;
	while (i < n_cmd)
	{
		if (wait_list[i] > 0)
			waitpid(wait_list[i++], &status, 0);
		else
			i++;
	}
}

int classic_manager(int argc, char **argv, char **env)
{
	int *wait_list;
	int n_cmd;
	int fd_io[2];
	int i;
	int j;

	i = 0;
	j = 0;
	n_cmd = get_n_cmd(argc, argv);
	fd_io[0] = open(argv[1], O_RDONLY);
	ft_putnbr_fd(n_cmd, 2);
	if (fd_io[0] < 0)
		error_input(argv[1], i++, n_cmd--);
	else
	{
		dup2(fd_io[0], STDIN_FILENO);
		close(fd_io[0]);
	}
	fd_io[1] = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_putnbr_fd(n_cmd, 2);
	wait_list = malloc((n_cmd) * sizeof(int));
	if (!wait_list)
		return (malloc_err());
	while (j < (n_cmd - 1))
		wait_list[j++] = create_pipe(argv[(i++) + 2], env);
	wait_list[j] = last_command(argc, argv, env, fd_io[1]);
	close_waitall(n_cmd, wait_list, fd_io);
	free(wait_list);
	return (0);
}

int heredoc_manager(int argc, char **argv, char **env)
{
	int *wait_list;
	int fd_io[2];
	int i;
	int n_cmd;

	fd_io[0] = create_here_doc_pipe(argv);
	dup2(fd_io[0], STDIN_FILENO);
	fd_io[1] = open(argv[argc-1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	n_cmd = get_n_cmd(argc, argv);
	wait_list = malloc(n_cmd * sizeof(int));
	if (!wait_list)
		return (malloc_err());
	i = 0;
	while (i < (n_cmd - 1))
	{
		wait_list[i] = create_pipe(argv[i + 3], env);
		i++;
	}
	wait_list[i++] = last_command(argc, argv, env, fd_io[1]);
	close_waitall(n_cmd, wait_list, fd_io);
	free(wait_list);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	if (argc >= 5)
	{
		if (str_cmp(argv[1], "here_doc") == 0)
		{
			if (argc >= 6)
				heredoc_manager(argc, argv, env);
		}
		else
			classic_manager(argc, argv, env);
	}
	return (0);
}
