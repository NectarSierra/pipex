/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:20:20 by nsaillez          #+#    #+#             */
/*   Updated: 2025/02/20 17:26:21 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

char *allocate_path(int i,char *str, char *cmd)
{
	char *selected_path;
	int j;
	int k;
	
	j = i;
	k = 0;
	while (str[i] && str[i] != ':')
		i++;
	while (cmd[k] && cmd[k] != ' ')
		k++;
	selected_path = malloc(((i + k) - j + 2) * sizeof(char));
	if (!selected_path)
		return (NULL);
	return (selected_path);
}

char *set_path(char *selected_path,int i, int j, char *cmd)
{
	int k;
	
	k = 0;		
	selected_path[i + k - j] = '/';
	k++;
	while (cmd[k-1] && cmd[k-1] != ' ')
	{
		selected_path[i + k - j] = cmd[k - 1];
		k++;
	}
	selected_path[i + k - j] = '\0';
	return (selected_path);
}

char *find_accessible_path(char *str, char *cmd)
{
	char *selected_path;
	int i;
	int j;
	
	j = 0;
	while (str[j] == '/')
	{
		i = j;
		selected_path = allocate_path(i, str, cmd);
		if (!selected_path)
			return (NULL);
		while (str[i] && str[i] != ':')
		{
			selected_path[i - j] = str[i];
			i++;
		}
		selected_path = set_path(selected_path, i, j, cmd);
		if (access(selected_path, F_OK) == 0)
			return (selected_path);
		free(selected_path);
		i++;
		j = i;
	}
	return (NULL);
}

int check_cmd_validity(char **env, char *cmd)
{
	char *result;
	
	result = find_accessible_path(srchstrsn(env, "PATH=", 5), cmd);
	if (result == NULL)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		free(result);
		return (-1);
	}
	free(result);
	return (0);
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
