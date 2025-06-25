/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:36:53 by prambaud          #+#    #+#             */
/*   Updated: 2025/06/25 16:59:57 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_in_brackets(char *line, int k)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 39 && check_next_quote(line, 39, i + 1))
			i += check_next_quote(line, 39, i + 1) + 2;
		else if (line[i] == 39 && line[i + 1] == 39)
			i += 2;
		else if (line[i] == 34 && check_next_quote(line, 34, i + 1))
			i = i + check_next_quote(line, 34, i + 1) + 2;
		else if (line[i] == 34 && line[i + 1] == 34)
			i += 2;
		else if (i == k)
			return (0);
		else
			i++;
	}
	return (1);
}

char	*suroundedPipe(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i + 1])
	{
		if (line[i] != '|' && line[i] != 32 && line[i + 1] == '|'
			&& !is_in_brackets(line, i + 1))
		{
			line = add_space(line, i + 1);
			if (!line)
				return (NULL);
			i++;
		}
		if (line[i] == '|' && line[i + 1] != 32 && line[i + 1] != '|'
			&& !is_in_brackets(line, i))
		{
			line = add_space(line, i + 1);
			if (!line)
				return (NULL);
			i++;
		}
		i++;
	}
	return (line);
}

char	*nonPipeSurounded2(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i + 1])
	{
		if (line[i] != '>' && line[i] != 32 && line[i + 1] == '>'
			&& !is_in_brackets(line, i + 1))
		{
			line = add_space(line, i + 1);
			if (!line)
				return (NULL);
			i++;
		}
		if (line[i] == '>' && line[i + 1] != 32 && line[i + 1] != '>'
			&& !is_in_brackets(line, i))
		{
			line = add_space(line, i + 1);
			if (!line)
				return (NULL);
			i++;
		}
		i++;
	}
	return (line);
}

char	*nonPipeSurounded(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i + 1])
	{
		if (line[i] != '<' && line[i] != 32 && line[i + 1] == '<'
			&& !is_in_brackets(line, i + 1))
		{
			line = add_space(line, i + 1);
			if (!line)
				return (NULL);
			i++;
		}
		if (line[i] == '<' && line[i + 1] != 32 && line[i + 1] != '<'
			&& !is_in_brackets(line, i))
		{
			line = add_space(line, i + 1);
			if (!line)
				return (NULL);
			i++;
		}
		i++;
	}
	return (line);
}

char	*une_histoire_de_pipe(char *line)
{
	line = suroundedPipe(line);
	if (!line)
		return (NULL);
	line = nonPipeSurounded(line);
	if (!line)
		return (NULL);
	line = nonPipeSurounded(line);
	if (!line)
		return (NULL);
	return (line);
}
