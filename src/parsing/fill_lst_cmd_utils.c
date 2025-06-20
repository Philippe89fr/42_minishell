/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lst_cmd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:25:46 by prambaud          #+#    #+#             */
/*   Updated: 2025/01/31 11:03:21 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	infile_outfile_count(t_token *lst_token, int indice)
{
	int		i;
	t_token	*current;

	i = 0;
	current = lst_token;
	while (current->prev && current->prev->type != PIPE)
		current = current->prev;
	while (current && current->type != PIPE)
	{
		if ((current->type == OUTPUT_APPEND || current->type == OUTPUT_TRUNC)
			&& indice == 1)
			i++;
		if ((current->type == INPUT) && indice == 2)
			i++;
		current = current->next;
	}
	return (i);
}

void	ft_lstnew_cmd_init2(t_cmd *new)
{
	new->full_cmd_malloc = 0;
	new->infile_malloc = 0;
	new->echo_arg_malloc = 0;
	new->limiters_malloc = 0;
	new->fail_outfile = 0;
	new->fail_infile = 0;
	new->outfile_tab = NULL;
	new->infile_tab = NULL;
	new->outfile_append_check_tab = NULL;
	new->outfile_tab_malloc = 0;
	new->infile_tab_malloc = 0;
	new->outfile_append_check_tab_malloc = 0;
	new->limiters = NULL;
	new->next_arg = NULL;
	new->next_arg_type = -1;
}

int	ft_lstnew_cmd_init(t_cmd *new, t_token *lst_token)
{
	ft_lstnew_cmd_init2(new);
	if (lst_token->next)
	{
		new->next_arg = lst_token->next->str;
		new->next_arg_type = lst_token->next->type;
	}
	new->cmd = lst_token->cmd;
	new->cmd_str = lst_token->str;
	new->full_cmd = check_args_cmd(lst_token);
	if (!new->full_cmd)
		return (1);
	new->full_cmd_malloc = 1;
	return (0);
}
