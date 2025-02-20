/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:59:47 by nsaillez          #+#    #+#             */
/*   Updated: 2025/02/20 13:53:52 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

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
	return (size + 1);
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

int str_cmp(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (-1);
		i++;
	}
	if (str1[i] == '\0' && str2[i] == '\n')
		return (0);
	if (str1[i] != str2[i])
		return (-1);
	return (0);
}

int get_n_cmd(int argc, char **argv)
{
	int n_cmd;
	// int i;
	
	// i = 0;
	if (str_cmp(argv[1], "here_doc") == 0)
		n_cmd = argc - 4;
	else
		n_cmd = argc - 3;
	// while (i < n_cmd)
	// {
	// 	if (check_cmd_validity(env, argv[i + 2]) == -1)
	// 		n_cmd--;
	// 	i++;
	// }
	return (n_cmd);
}
