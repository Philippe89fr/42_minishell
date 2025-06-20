/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:26:33 by prambaud          #+#    #+#             */
/*   Updated: 2025/01/28 09:42:52 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_cmd(t_token *token)
{
	t_token	*current;

	current = token;
	while (current && current->type != PIPE)
	{
		if (current->type == CMD)
			return (0);
		current = current->prev;
	}
	return (1);
}

/*on assigne a ce nouveau noeud le type correspondant
a sa strcd n etant pas lu correctement par execve,
il faut donc un chemin special
le token->cmd = ft_strdup(str) ayant lieu dans
access_check il faut aussi le faire ici*/
int	def_type_token(char *str, t_token *token)
{
	if (ft_strncmp(str, ">", 2) == 0)
		return (OUTPUT_TRUNC);
	else if (ft_strncmp(str, "<<", 3) == 0)
		return (HERE_DOC);
	else if (ft_strncmp(str, ">>", 3) == 0)
		return (OUTPUT_APPEND);
	else if (ft_strncmp(str, "|", 2) == 0 || ft_strncmp(str, "||", 3) == 0)
		return (PIPE);
	else if (ft_strncmp(str, "<", 2) == 0)
		return (INPUT);
	else if ((is_cmd(token->prev) && (token->prev
				&& (token->prev->type != OUTPUT_TRUNC
					&& token->prev->type != OUTPUT_APPEND
					&& token->prev->type != INPUT
					&& token->prev->type != HERE_DOC))) || (is_cmd(token->prev)
			&& !token->prev))
		return (CMD);
	else
		return (ARG);
}
