/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   une_line_dans_la_nature_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:36:53 by prambaud          #+#    #+#             */
/*   Updated: 2025/01/31 12:04:11 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_space(char *line, int i)
{
	int		j;
	char	*copy_line;

	copy_line = (char *)malloc((ft_strlen(line) + 2) * sizeof(char));
	if (!copy_line)
		return (malloc_fail(), free(line), NULL);
	j = 0;
	while (j != i)
	{
		copy_line[j] = line[j];
		j++;
	}
	copy_line[j] = ' ';
	while (line[i])
	{
		copy_line[i + 1] = line[i];
		i++;
	}
	copy_line[i + 1] = '\0';
	free(line);
	return (copy_line);
}
/*
-> trois >>> ||| <<< etc
-> < > >> << sans arguments
-> | | pipe sans rien avant ou apres ou au milieu fermer
-> un ou plusieurs & -> ciao
*/

int	trois_trucs_et_cest_foutu(char *line, char truc)
{
	int	i;

	i = 0;
	while (line[i] && line[i + 1] && line[i + 2])
	{
		if (line[i] == truc && line[i + 1] == truc && line[i + 2] == truc
			&& !is_in_brackets(line, i))
			return (1);
		i++;
	}
	return (0);
}

int	il_y_a_et_ciao(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '&')
			return (1);
		i++;
	}
	return (0);
}

int	null_apres_un_truc(t_token *token)
{
	if (token->type == INPUT && !token->next)
		return (ft_printf("minishell: syntax error near unexpected token `<'\n"),
			1);
	else if (token->type == PIPE && !token->next)
	{
		ft_printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	else if (token->type == OUTPUT_TRUNC && !token->next)
	{
		ft_printf("minishell: syntax error near unexpected token `>'\n");
		return (1);
	}
	else if (token->type == OUTPUT_APPEND && !token->next)
	{
		ft_printf("minishell: syntax error near unexpected token `>>'\n");
		return (1);
	}
	else if ((token->type == HERE_DOC) && !token->next)
	{
		ft_printf("minishell: syntax error near unexpected token `<<'\n");
		return (1);
	}
	return (0);
}

/*regarde les tokens */
int	check_linked_token(t_token *token)
{
	if (token->type == PIPE)
	{
		if ((!token->prev || (token->prev->type != ARG
					&& token->prev->type != CMD)) || (!token->next
				|| (token->next->type == PIPE)))
		{
			ft_printf("minishell: syntax error near unexpected token `|'\n");
			return (1);
		}
	}
	if (token->type == INPUT || token->type == OUTPUT_TRUNC
		|| token->type == OUTPUT_APPEND || token->type == HERE_DOC)
	{
		if (!token->next || token->next->type != ARG)
		{
			if (token->type == INPUT || token->type == HERE_DOC)
				ft_printf("minishell: syntax error near unexpected token `<'\n");
			else
				ft_printf("minishell: syntax error near unexpected token `>'\n");
			return (1);
		}
	}
	return (0);
}
