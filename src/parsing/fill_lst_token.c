/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lst_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                        int                        +#+#+#+#+#+
	+#+           */
/*   Created: 2025/01/08 11:42:34 by prambaud          #+#    #+#             */
/*   Updated: 2025/01/09 13:30:41 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*on cree un nouveau noeud dans la liste chainee
ft_strdup utilise pour pouvoir liberer tab_line dans main lexing*/
t_token	*ft_lstnew_token(void *str)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str_malloc = 0;
	new->cmd_malloc = 0;
	new->str = ft_strdup(str);
	if (!new->str)
	{
		free(new);
		return (NULL);
	}
	new->str_malloc = 1;
	new->cmd = NULL;
	new->next = NULL;
	return (new);
}

/*on prend le tableaux d'instructions cree precedemment pour en
faire une liste chainee avec un element dans chaque
a la fin on cree fait le lien avec les precedents via lst_token_put_back.
Une fois cela fait nous pouvons finaliser l initialisation
des types de chaque token qui necessite de regarder
en arriere */
t_token	*lst_token_maker2(char **tab_line)
{
	t_token	*lst_token;
	t_token	*new_node;
	int		i;

	i = 0;
	lst_token = NULL;
	while (tab_line[i])
	{
		new_node = ft_lstnew_token(tab_line[i]);
		if (!new_node)
		{
			ft_lstclear_token(&lst_token);
			return (malloc_fail(), NULL);
		}
		ft_lstadd_back_token(&lst_token, new_node);
		i++;
	}
	lst_token_put_back(lst_token);
	new_node = lst_token;
	while (new_node)
	{
		new_node->type = def_type_token(new_node->str, new_node);
		new_node = new_node->next;
	}
	return (lst_token);
}

/*Recupere la ligne de Readline, la split et la transformer en list chainee*/
t_token	*lst_token_maker(char *line, t_pipex *pipex)
{
	char	**tab_line;
	t_token	*lst_token;
	t_token	*current;

	tab_line = ft_split(line, 25);
	if (!tab_line)
		return (free(line), NULL);
	if (!tab_line[0])
		return (free(line), ft_liberator_max(tab_line), NULL);
	free(line);
	lst_token = lst_token_maker2(tab_line);
	if (!lst_token)
		return (ft_liberator_max(tab_line), NULL);
	current = lst_token;
	while (current)
	{
		access_check(current, pipex);
		current = current->next;
	}
	if (def_empty_or_false_cmd_token(lst_token))
		return (ft_liberator_max(tab_line), NULL);
	ft_liberator_max(tab_line);
	return (lst_token);
}
