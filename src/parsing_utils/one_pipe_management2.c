/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_pipe_management2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:36:53 by prambaud          #+#    #+#             */
/*   Updated: 2025/06/25 17:03:13 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	twoPipeCheck(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i + 1])
	{
		if (line[i] == '|' && line[i + 1] == '|' && !is_in_brackets(line, i))
		{
			if (!line[i + 2])
				return (1);
			else
			{
				while (line[i])
				{
					line[i] = '\0';
					i++;
				}
				return (0);
			}
		}
		i++;
	}
	return (0);
}

int	verif_line_caracteres(char *line, t_pipex *pipex)
{
	int	i;

	i = -1;
	if (removeWhenTree(line, '>'))
		i = ft_printf("minishell: syntax error near unexpected token `>'\n");
	else if (removeWhenTree(line, '<'))
		i = ft_printf("minishell: syntax error near unexpected token `<'\n");
	else if (removeWhenTree(line, '|'))
		i = ft_printf("minishell: syntax error near unexpected token `|'\n");
	else if (charFinder(line))
	{
		i = ft_printf("minishell: syntax error,");
		ft_printf("our minishell does not understand `&'\n");
	}
	if (i > -1)
	{
		pipex->status = 2;
		pipex->status_check = 1;
		return (1);
	}
	return (0);
}

int	verif_tokens(t_token *lst_token, t_pipex *pipex)
{
	t_token	*current;

	current = lst_token;
	while (current)
	{
		if (check_linked_token(current) || null_apres_un_token(current))
		{
			pipex->status = 2;
			pipex->status_check = 1;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	removeSpace(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 32 && !is_in_brackets(line, i))
			line[i] = 25;
		i++;
	}
}

char	*parsing_champetre(char *line, t_pipex *pipex)
{
	char	**tab_line;
	t_token	*lst_token;

	line = une_histoire_de_pipe(line);
	if (!line)
		return (NULL);
	if (verif_line_caracteres(line, pipex))
		return (free(line), NULL);
	removeSpace(line);
	tab_line = ft_split(line, 25);
	if (!tab_line)
		return (malloc_fail(), free(line), NULL);
	if (!tab_line[0])
		return (free(tab_line), free(line), NULL);
	lst_token = lst_token_maker2(tab_line);
	if (!lst_token)
		return (free(line), NULL);
	if (verif_tokens(lst_token, pipex))
		return (free(line), ft_lstclear_token(&lst_token),
			ft_liberator_max(tab_line), NULL);
	twoPipeCheck(line);
	ft_lstclear_token(&lst_token);
	ft_liberator_max(tab_line);
	return (line);
}
