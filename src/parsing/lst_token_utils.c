/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:03:57 by prambaud          #+#    #+#             */
/*   Updated: 2025/01/21 16:27:31 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*ici,
	nous mettons en place un lien qui dirige
	vers le noeud precedent chaque noeud.
Le premier noeud previous est NULL*/
void	lst_token_put_back(t_token *lst_token)
{
	t_token	*current;
	t_token	*previous;

	previous = lst_token;
	previous->prev = NULL;
	current = previous->next;
	while (current)
	{
		current->prev = previous;
		previous = current;
		current = current->next;
	}
}

void	ft_print_lst_token(t_token *lst_token)
{
	t_token	*current;
	int		i;

	i = 0;
	current = lst_token;
	while (current)
	{
		ft_printf("N%d:\nLa string %s\nLa cmd %s\nLe type :%d\n\n", i,
			current->str, current->cmd, current->type);
		current = current->next;
		i++;
	}
}

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*current;

	if (!lst || lst == &new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = ft_lstlast_token(*lst);
	current->next = new;
}

t_token	*ft_lstlast_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize_token(t_token *lst)
{
	int		count;
	t_token	*current;

	count = 0;
	current = lst;
	while (current)
	{
		current = current->next;
		count++;
	}
	return (count);
}
