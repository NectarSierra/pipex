/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_valid_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:20:20 by nsaillez          #+#    #+#             */
/*   Updated: 2025/02/18 16:35:46 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/libft.h"

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
	ft_putstr_fd("Error - command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}
