/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lst_cmd_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:25:46 by prambaud          #+#    #+#             */
/*   Updated: 2025/01/31 10:41:38 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tab_outfile2(t_token *current, char **tab)
{
	int	i;

	i = 0;
	while (current && current->type != PIPE)
	{
		if (current->next && (current->type == OUTPUT_APPEND
				|| current->type == OUTPUT_TRUNC))
		{
			tab[i] = current->next->str;
			i++;
		}
		current = current->next;
	}
	tab[i] = NULL;
}

char	**tab_outfile(t_token *lst_token)
{
	char	**tab;
	t_token	*current;

	current = lst_token;
	if (infile_outfile_count(lst_token, 1) == 0)
		return (NULL);
	tab = (char **)malloc((infile_outfile_count(lst_token, 1) + 1)
			* sizeof(char *));
	if (!tab)
		return (malloc_fail(), NULL);
	while (current->prev && current->prev->type != PIPE)
		current = current->prev;
	tab_outfile2(current, tab);
	return (tab);
}

char	**tab_infile(t_token *lst_token)
{
	char	**tab;
	t_token	*current;
	int		i;

	i = 0;
	current = lst_token;
	if (infile_outfile_count(lst_token, 2) == 0)
		return (NULL);
	tab = (char **)malloc((infile_outfile_count(lst_token, 2) + 1)
			* sizeof(char *));
	if (!tab)
		return (malloc_fail(), NULL);
	while (current->prev && current->prev->type != PIPE)
		current = current->prev;
	while (current && current->type != PIPE)
	{
		if (current->type == INPUT)
		{
			tab[i] = current->next->str;
			i++;
		}
		current = current->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	tab_int_outfile2(t_token *current, int *tab)
{
	int	i;

	i = 0;
	while (current && current->type != PIPE)
	{
		if (current->type == OUTPUT_APPEND)
		{
			tab[i] = 1;
			i++;
		}
		if (current->type == OUTPUT_TRUNC)
		{
			tab[i] = 0;
			i++;
		}
		current = current->next;
	}
}

int	*tab_int_outfile(t_token *lst_token)
{
	int		*tab;
	t_token	*current;

	current = lst_token;
	if (infile_outfile_count(lst_token, 1) == 0)
		return (NULL);
	tab = (int *)malloc(infile_outfile_count(lst_token, 1) * sizeof(int));
	if (!tab)
		return (malloc_fail(), NULL);
	while (current->prev && current->prev->type != PIPE)
		current = current->prev;
	tab_int_outfile2(current, tab);
	return (tab);
}
