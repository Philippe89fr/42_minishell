/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token_take_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:32:25 by prambaud          #+#    #+#             */
/*   Updated: 2025/01/31 11:30:10 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmd_until_pipe_check(t_token *token)
{
	t_token	*current;

	current = token;
	while (current->prev && current->prev->type != PIPE)
		current = current->prev;
	while (current && current->type != PIPE)
	{
		if (current->type == CMD)
			return (1);
		current = current->next;
	}
	return (0);
}

void	first_arg_not_doc_turn_command(t_token *token)
{
	t_token	*current;

	current = token;
	while (current && current->type != PIPE)
	{
		if (current->prev->type && current->type == ARG
			&& (current->prev->type != OUTPUT_TRUNC
				|| current->prev->type != OUTPUT_APPEND
				|| current->prev->type != INPUT
				|| current->prev->type != HERE_DOC))
		{
			current->type = CMD;
			return ;
		}
		current = current->next;
	}
	return ;
}

t_token	*ft_lstnew_token_fake_empty_cmd(void)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str_malloc = 0;
	new->cmd_malloc = 0;
	new->str = ft_strdup("fake_fdp");
	if (!new->str)
	{
		free(new);
		return (NULL);
	}
	new->str_malloc = 1;
	new->type = CMD;
	new->cmd = NULL;
	new->next = NULL;
	return (new);
}

/*check s'il y a bien une commande,
	s il y en a pas en assigne une de force en choisissant le premier ARG.
Si vraiment aucune option alors la CMD est NULL*/
int	def_empty_or_false_cmd_token_else(t_token *current)
{
	t_token	*new;
	t_token	*temp;

	temp = current;
	while (temp->next && temp->next->type != PIPE)
		temp = temp->next;
	new = ft_lstnew_token_fake_empty_cmd();
	if (!new)
		return (malloc_fail(), 1);
	new->next = temp->next;
	temp->next = new;
	new->prev = temp;
	return (0);
}

int	def_empty_or_false_cmd_token(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (cmd_until_pipe_check(current))
		{
			while (current && current->type != PIPE)
				current = current->next;
			if (current)
				current = current->next;
		}
		else
		{
			if (def_empty_or_false_cmd_token_else(current))
				return (1);
		}
		if (current)
			current = current->next;
	}
	return (0);
}
