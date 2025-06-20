/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:38:16 by prambaud          #+#    #+#             */
/*   Updated: 2025/01/31 11:17:57 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize_cmd(t_cmd *lst)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = lst;
	while (current)
	{
		current = current->next;
		count++;
	}
	return (count);
}

/*trouver le dernier noeud*/
t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*ajouter le noeud a la fin*/
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*current;

	if (!lst || lst == &new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = ft_lstlast_cmd(*lst);
	current->next = new;
}
