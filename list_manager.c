/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaillez <nsaillez@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:18:00 by nsaillez          #+#    #+#             */
/*   Updated: 2025/02/12 09:01:14 by nsaillez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_list *create_list()
{
	t_list *root;
	
	root = malloc(sizeof(t_list));
	if (root != NULL)
	{
		root->next = NULL;
		root->fd_next = -1;
		root->fd_previous = -1;
		root->command = NULL;
	}
	return (root);
}

void add_new_node(t_list *node, char *command)
{
	t_list *element;
	t_list *current;

	current = node;
	while (current->next != NULL)
		current = current->next;
	element = malloc(sizeof(t_list));
	if (element != NULL)
	{
		element->next = NULL;
		element->command = command;
		current->next = element;
	}
}
