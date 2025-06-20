/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lst_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:35:24 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/13 14:10:29 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*On cherche le dernier infile lie a une commande et on le renvoie*/
/*on cree full_cmd avec la taille du nombre d'arguments + le chemin et la cmd :
on rempli lst_cmd->full_cmd[0] avec le chemin deja renseigne dans le lst_token
puis on met les arguments*/

void	check_args_cmd2(char **full_cmd, t_token *lst_token)
{
	t_token	*current;
	int		i;

	i = 1;
	current = lst_token->next;
	full_cmd[0] = lst_token->cmd;
	while (current && current->type != PIPE)
	{
		if (current->type == ARG && (current->prev->type == CMD
				|| current->prev->type == ARG))
		{
			full_cmd[i] = current->str;
			i++;
		}
		current = current->next;
	}
	full_cmd[i] = NULL;
}

char	**check_args_cmd(t_token *lst_token)
{
	t_token	*current;
	char	**full_cmd;
	int		i;

	i = 1;
	current = lst_token->next;
	while (current && current->type != PIPE)
	{
		if (current->type == ARG && (current->prev->type == CMD
				|| current->prev->type == ARG))
			i++;
		current = current->next;
	}
	full_cmd = (char **)malloc((i + 1) * sizeof(char *));
	if (!full_cmd)
		return (malloc_fail(), NULL);
	check_args_cmd2(full_cmd, lst_token);
	return (full_cmd);
}

/*on cree un nouveau noeud dans la liste chainee
une fonction pour chaque element du noued/commande */
/*new->cmd contient la commande mais aussi son chemin*/

int	ft_lstnew_cmd2(t_token *lst_token, t_cmd *new)
{
	new->outfile_tab = tab_outfile(lst_token);
	if (new->outfile_tab)
		new->outfile_tab_malloc = 1;
	if (!new->outfile_tab && infile_outfile_count(lst_token, 1))
		return (1);
	new->infile_tab = tab_infile(lst_token);
	if (new->infile_tab)
		new->infile_tab_malloc = 1;
	if (!new->infile_tab && infile_outfile_count(lst_token, 2))
		return (1);
	new->outfile_append_check_tab = tab_int_outfile(lst_token);
	if (new->outfile_append_check_tab)
		new->outfile_append_check_tab_malloc = 1;
	if (!new->outfile_append_check_tab && infile_outfile_count(lst_token, 1))
		return (1);
	new->next = NULL;
	return (0);
}

t_cmd	*ft_lstnew_cmd(t_token *lst_token, char c)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (malloc_fail(), NULL);
	if (ft_lstnew_cmd_init(new, lst_token))
		return (NULL);
	new->infile = check_infile_cmd(lst_token);
	if (lst_cmd_init_here_doc(new, lst_token, c))
		return (NULL);
	new->outfile = check_outfile_cmd(lst_token);
	new->outfile_append_check = check_outfile_append(lst_token);
	new->path_check = 0;
	if (new->cmd && ft_strchr(new->cmd, '/'))
		new->path_check = 1;
	if (ft_lstnew_cmd2(lst_token, new))
		return (NULL);
	new->echo_arg = echo_arg(new, lst_token, 0);
	if (!new->echo_arg && !ft_strncmp(lst_token->str, "echo", 5))
		return (new);
	return (new);
}

/*En parcourant la liste chaine de token,
	on cree une nouvelle liste chaine de commande */
t_cmd	*lst_cmd_maker(t_token *lst_token)
{
	t_cmd	*lst_cmd;
	t_cmd	*new_node;
	t_token	*current;
	char	c;

	c = 'a';
	current = lst_token;
	lst_cmd = NULL;
	while (current)
	{
		if (current->type == CMD)
		{
			new_node = ft_lstnew_cmd(current, c);
			if (!new_node)
			{
				ft_lstclear_cmd(&lst_cmd);
				return (NULL);
			}
			ft_lstadd_back_cmd(&lst_cmd, new_node);
			c++;
		}
		current = current->next;
	}
	return (lst_cmd);
}
