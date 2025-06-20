/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lst_cmd_here_doc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:44:31 by lbenatar          #+#    #+#             */
/*   Updated: 2025/01/31 11:04:08 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Cherche si l infile est un here_doc ou non*/
int	check_last_infile_cmd(t_token *lst_token)
{
	t_token	*current;
	int		here_doc;

	current = lst_token;
	here_doc = 0;
	while (current && current->prev && current->prev->type != PIPE)
		current = current->prev;
	while (current && current->type != PIPE)
	{
		if (current->next && current->type == INPUT)
			here_doc = 0;
		if (current->next && current->type == HERE_DOC)
			here_doc = 1;
		current = current->next;
	}
	return (here_doc);
}

/*cree un fichier temp pour recevoir l input de la commande here_doc
fichier inexistant qui va etre unlik plus tard
malloc protect*/
char	*create_temp_here_doc(char c)
{
	char	*here_doc;

	here_doc = (char *)malloc(sizeof(char) * 2);
	if (!here_doc)
		return (malloc_fail(), NULL);
	here_doc[0] = c;
	here_doc[1] = '\0';
	while (access(here_doc, F_OK) == 0)
	{
		here_doc = ft_strjoin5(here_doc, "_");
		if (!here_doc)
			return (malloc_fail(), NULL);
	}
	return (here_doc);
}

/*cette fonction permet de compter le nombre d'here_doc par commande*/
int	count_here_doc(t_token *lst_token)
{
	t_token	*current;
	int		count_here_doc;

	current = lst_token;
	count_here_doc = 0;
	while (current && current->prev && current->prev->type != PIPE)
		current = current->prev;
	while (current && current->type != PIPE)
	{
		if (current->type == HERE_DOC && current->next)
			count_here_doc++;
		current = current->next;
	}
	return (count_here_doc);
}

/*Initialisation d une partie de la partie here_doc en creant
un tableau de tableau qui va contenir tous les limiters
malloc protect*/
char	**fill_cmd_limiters(t_token *lst_token, int count_here_doc)
{
	t_token	*current;
	char	**limiters;
	int		i;

	current = lst_token;
	limiters = (char **)malloc(sizeof(char *) * (count_here_doc + 1));
	if (!limiters)
		return (malloc_fail(), NULL);
	while (current && current->prev && current->prev->type != PIPE)
		current = current->prev;
	i = 0;
	while (current && current->type != PIPE)
	{
		if (current->next && (current->type == HERE_DOC))
		{
			limiters[i] = current->next->str;
			i++;
		}
		current = current->next;
	}
	limiters[i] = NULL;
	return (limiters);
}

/*initialisation de la partie here_doc de la commande*/
int	lst_cmd_init_here_doc(t_cmd *new, t_token *lst_token, char c)
{
	new->count_here_doc = count_here_doc(lst_token);
	new->infile_here_doc = check_last_infile_cmd(lst_token);
	if (new->count_here_doc > 0)
	{
		new->limiters = fill_cmd_limiters(lst_token, new->count_here_doc);
		if (!new->limiters)
			return (1);
		new->limiters_malloc = 1;
	}
	if (new->infile_here_doc)
	{
		new->infile = create_temp_here_doc(c);
		if (!new->infile)
			return (1);
		new->infile_malloc = 1;
	}
	return (0);
}
