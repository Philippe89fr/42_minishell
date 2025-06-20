/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:19:18 by prambaud          #+#    #+#             */
/*   Updated: 2025/01/30 17:35:01 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*On cherche le dernier >> lie a une commande et on le renvoie*/
int	check_outfile_append(t_token *lst_token)
{
	t_token	*current;
	char	*outfile;
	int		indice;

	indice = 0;
	current = lst_token;
	outfile = NULL;
	while (current && current->prev && current->prev->type != PIPE)
		current = current->prev;
	while (current && current->type != PIPE)
	{
		if (current->type == OUTPUT_APPEND)
			indice = 1;
		if (current->type == OUTPUT_TRUNC)
			indice = 0;
		current = current->next;
	}
	return (indice);
}

/*On cherche le dernier outfile lie a une commande et on le renvoie*/
char	*check_outfile_cmd(t_token *lst_token)
{
	t_token	*current;
	char	*outfile;

	current = lst_token;
	outfile = NULL;
	while (current && current->prev && current->prev->type != PIPE)
		current = current->prev;
	while (current && current->type != PIPE)
	{
		if (current->next && (current->type == OUTPUT_APPEND
				|| current->type == OUTPUT_TRUNC))
			outfile = current->next->str;
		current = current->next;
	}
	return (outfile);
}

/*On cherche le dernier infile lie a une commande et on le renvoie*/
char	*check_infile_cmd(t_token *lst_token)
{
	t_token	*current;
	char	*infile;

	current = lst_token;
	infile = NULL;
	while (current && current->prev && current->prev->type != PIPE)
		current = current->prev;
	while (current && current->type != PIPE)
	{
		if (current->next && current->type == INPUT)
			infile = current->next->str;
		current = current->next;
	}
	return (infile);
}
