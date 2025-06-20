/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_management2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:08:47 by lbenatar          #+#    #+#             */
/*   Updated: 2025/01/31 11:35:05 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*search_env(char *line, t_pipex *pipex, int format)
{
	int		i;
	int		j;
	char	*variable;

	i = 0;
	j = 0;
	while (line[i] && char_is_ok(line[i]))
		i++;
	pipex->compteur_characters += i + 1;
	while ((pipex->env[j] && !(ft_strncmp(pipex->env[j], line, i) == 0
				&& pipex->env[j][i] == '=')))
		j++;
	variable = search_env_get_variable(i, j, pipex, format);
	if (!variable)
		return (NULL);
	return (variable);
}

int	get_segmenting_brackets_size(char *line)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] && (!line[i + 1] || line[i] != '$'
				|| !char_is_ok(line[i + 1])))
		{
			while (line[i] && (!line[i + 1] || line[i] != '$'
					|| !char_is_ok(line[i + 1])))
				i++;
			j++;
		}
		if (line[i] == '$' && line[i + 1] && char_is_ok(line[i + 1]))
		{
			i++;
			while (line[i] && char_is_ok(line[i]))
				i++;
			j++;
		}
	}
	return (j);
}

int	fill_segmenting_brackets_i(int i, char *line, int indice)
{
	if (indice == 1)
	{
		while (line[i] && (!line[i + 1] || line[i] != '$'
				|| !char_is_ok(line[i + 1])))
			i++;
	}
	if (indice == 0)
	{
		i++;
		while (line[i] && char_is_ok(line[i]))
			i++;
	}
	return (i);
}

int	fill_segmenting_brackets(int i, char *line, char **segmented_brackets,
		t_pipex *pipex)
{
	int	t;

	t = 0;
	while ((size_t)i <= ft_strlen(line) && line[i])
	{
		if (line[i] && (!line[i + 1] || line[i] != '$'
				|| !char_is_ok(line[i + 1])))
		{
			segmented_brackets[t] = get_part_without_dollars(line, i);
			if (!segmented_brackets[t])
				return (ft_liberator_max(segmented_brackets), 1);
			i = fill_segmenting_brackets_i(i, line, 1);
			t++;
		}
		if (line[i] == '$' && line[i + 1] && char_is_ok(line[i + 1]))
		{
			segmented_brackets[t] = search_env(&line[i + 1], pipex, 0);
			if (!segmented_brackets[t])
				return (ft_liberator_max(segmented_brackets), 1);
			i = fill_segmenting_brackets_i(i, line, 0);
			t++;
		}
	}
	return (0);
}

char	**segmenting_brackets(char *line, t_pipex *pipex)
{
	int		j;
	int		i;
	char	**segmented_brackets;

	j = get_segmenting_brackets_size(line);
	segmented_brackets = (char **)malloc(sizeof(char *) * (j + 1));
	if (!segmented_brackets)
		return (NULL);
	i = 0;
	while (i <= j)
	{
		segmented_brackets[i] = 0;
		i++;
	}
	i = 0;
	if (fill_segmenting_brackets(i, line, segmented_brackets, pipex))
		return (NULL);
	return (segmented_brackets);
}
