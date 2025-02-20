/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:49:19 by nsaillez          #+#    #+#             */
/*   Updated: 2025/02/20 14:17:01 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

int create_pipe(char *command, char **env)
{
	int pipe_fd[2];
	pid_t pid;
	
	if (pipe(pipe_fd) < 0)
		return (pipe_err());
	if (check_cmd_validity(env, command) >= 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (fork_err());
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		if (check_cmd_validity(env, command) >= 0)
			execute_cmd(command, env);
		exit(1);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		return (pid);
	}
}

void put_in_pipe(char **argv, int *pipe_fd)
{
	char *res;
	res = get_next_line(0);
	while(res != NULL && str_cmp(argv[2], res) == -1)
	{
		ft_putstr_fd(res, pipe_fd[1]);
		free(res);
		res = get_next_line(0);
	}
	free(res);
}

int create_here_doc_pipe(char **argv)
{
	int pipe_fd[2];
	pid_t pid;

	if(pipe(pipe_fd) < 0)
		return (pipe_err());
	pid = fork();
	if (pid == -1)
		return (fork_err());
	if (pid == 0)
	{
		close(pipe_fd[0]);
		put_in_pipe(argv, pipe_fd);
		close(pipe_fd[1]);
		exit(0);
	}
	else if (pid > 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		wait(NULL);
	}
	return (pipe_fd[0]);
}

int last_command(int argc,char **argv, char **env, int fd_out)
{
	pid_t pid;

	if (check_cmd_validity(env, argv[argc - 2]) == -1)
		return (-1);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	pid = fork();
	if (pid == 0)
	{
		if(execute_cmd(argv[argc - 2], env) == -1)
		{
			perror("excve error:");
			exit(1);
		}
	}
	return (pid);
}
