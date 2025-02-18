/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:49:19 by nsaillez          #+#    #+#             */
/*   Updated: 2025/02/18 16:58:57 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/libft.h"

int get_cmd_size(char *cmd)
{
	int size;
	
	size = 0;
	while (cmd[size] && cmd[size] != ' ')
	{
		size++;
	}
	if (cmd[size] != ' ')
		return (0);
	return (size+1);
}

char *srchstrsn(char **lst_haystack, char *needle, int len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (lst_haystack[i])
	{
		j = 0;
		while ((lst_haystack[i][j] == needle[j]) && j < len)
			j++;
		if (j == len)
			return (lst_haystack[i] + j);
		i++;
	}
	return (NULL);
}

int execute_cmd(char *cmd, char **env)
{
	char *argv[3];
	int size;
	
	size = get_cmd_size(cmd);
	argv[0] = find_accessible_path(srchstrsn(env, "PATH=", 5), cmd);
	if (!argv[0])
		return (-2);
	if (size == 0)
		argv[1] = NULL;
	else
		argv[1] = cmd + size;
	argv[2] = NULL;
	if(execve(argv[0], argv, NULL) == -1)
	{
		perror("excve failed");
		return (-1);
	}
	return (0);
}

int create_pipe(char *command, char **env)
{
	int pipe_fd[2];
	pid_t pid;
	
	if(pipe(pipe_fd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		if(execute_cmd(command, env) < 0)
			exit(EXIT_FAILURE);
		return (-1);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		wait(NULL);
		return (pid);
	}
}

int str_cmp(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (-1);
		i++;
	}
	
	return (0);
}

void here_doc(char **argv)
{
	char *res;
	int pipe_fd[2];
	pid_t pid;

	pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		close(pipe_fd[0]);
		res = get_next_line(0);
		while(res != NULL && str_cmp(res, argv[2]) == -1)
		{
			ft_putstr_fd(res, pipe_fd[1]);
			free(res);
			res = get_next_line(0);
		}
		free(res);
		exit(0);
	}
	else if (pid > 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		wait(NULL);
	}
}

int main(int argc, char **argv, char **env)
{
	int i;
	int fd_inout[2];
	int fd_heredoc;
	int wait_list[argc - 1];
	int status;

	if (argc >= 5)
	{
		// here doc
		// else
		// last command to output
		// waipid
		int j = 0;
		i = 2;
		if (str_cmp(argv[1], "here_doc") == 0)
		{
			fd_heredoc = open(argv[argc-1], O_CREAT | O_WRONLY | O_APPEND, 0777);
			if (fd_heredoc == -1)
				printf("failed\n");
			here_doc(argv);
			i = 3;
		}
		else
		{
			get_inout_fd(fd_inout, argc, argv);
			if (fd_inout[0] < 0)
			{
				ft_putstr_fd("Error - no such a file or directory: ", 2);
				ft_putstr_fd(argv[1], 2);
				ft_putstr_fd("\n", 2);
				i++;
			}
			dup2(fd_inout[0], STDIN_FILENO);
		}
		while (i < argc - 2)
			wait_list[j++] = create_pipe(argv[i++], env);
		if (str_cmp(argv[1], "here_doc") == 0)
			dup2(fd_heredoc, STDOUT_FILENO);
		else
			dup2(fd_inout[1], STDOUT_FILENO);
		pid_t pid = fork();
		if (pid == 0)
			execute_cmd(argv[i], env);
		wait_list[j++] = pid;
		j = 0;
		while (j < argc - (i))
			waitpid(wait_list[j++], &status, 0);
		return (pid);
	}
	return (0);
}
