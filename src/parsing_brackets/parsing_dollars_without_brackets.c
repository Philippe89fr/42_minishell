/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollars_without_brackets.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:08:56 by lbenatar          #+#    #+#             */
/*   Updated: 2025/01/31 11:38:21 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	segmented_brackets_size_calculator(char *line, int i, int j)
{
	while (line[i])
	{
		if (line[i] && !check_line(line, i) && (!line[i + 1] || line[i] != '$'
				|| !char_is_ok(line[i + 1])))
		{
			while (line[i] && (!line[i + 1] || line[i] != '$'
					|| !char_is_ok(line[i + 1])) && !check_line(line, i))
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
		if (line[i] && line[i] && (!line[i + 1] || line[i] != '$'
				|| !char_is_ok(line[i + 1])) && check_line(line, i))
		{
			i += check_next_quote(line, line[i], i + 1) + 2;
			j++;
		}
	}
	return (j);
}

int	ft_increasing_i(int i, char *line, int indice)
{
	if (indice == 1)
	{
		while (line[i] && !check_line(line, i) && (!line[i + 1]
				|| line[i] != '$' || !char_is_ok(line[i + 1])))
			i++;
	}
	if (indice == 2)
	{
		i++;
		while (line[i] && char_is_ok(line[i]))
			i++;
	}
	if (indice == 3)
	{
		i += check_next_quote(line, line[i], i + 1) + 2;
	}
	return (i);
}

int	ft_parsing_dollars_boucle_if(char *line, char **segmented_brackets, int i,
		int t)
{
	if ((!line[i + 1] || line[i] != '$' || !char_is_ok(line[i + 1]))
		&& !check_line(line, i) && line[i])
	{
		segmented_brackets[t] = get_part_without_dollars2(line, i);
		if (!segmented_brackets[t])
			return (ft_liberator_max(segmented_brackets), -1);
		i = ft_increasing_i(i, line, 1);
	}
	else if ((!line[i + 1] || line[i] != '$' || !char_is_ok(line[i + 1]))
		&& check_line(line, i) && line[i])
	{
		segmented_brackets[t] = get_part_with_brackets(line, i);
		if (!segmented_brackets[t])
			return (ft_liberator_max(segmented_brackets), -1);
		i = ft_increasing_i(i, line, 3);
	}
	return (i);
}

int	ft_parsing_dollars_boucle(char *line, t_pipex *pipex,
		char **segmented_brackets, int i)
{
	int	t;
	int	inc;

	t = 0;
	while (line[i])
	{
		inc = ft_parsing_dollars_boucle_if(line, segmented_brackets, i, t);
		if (inc > i)
		{
			i = inc;
			t++;
		}
		else if (inc == -1)
			return (1);
		else if (line[i] && line[i] == '$' && line[i + 1]
			&& char_is_ok(line[i + 1]))
		{
			segmented_brackets[t] = search_env(&line[i + 1], pipex, 1);
			if (!segmented_brackets[t])
				return (ft_liberator_max(segmented_brackets), 1);
			i = ft_increasing_i(i, line, 2);
			t++;
		}
	}
	return (0);
}

char	*ft_parsing_dollars_without_brackets(char *line, t_pipex *pipex)
{
	int		t;
	char	**segmented_brackets;
	char	*new_line;

	t = segmented_brackets_size_calculator(line, 0, 0);
	segmented_brackets = (char **)malloc(sizeof(char *) * (t + 1));
	if (!segmented_brackets)
		return (NULL);
	segmented_brackets[t] = 0;
	if (line && ft_parsing_dollars_boucle(line, pipex, segmented_brackets, 0))
		return (NULL);
	t = 0;
	new_line = ft_strdup(segmented_brackets[t]);
	if (!new_line)
		return (ft_liberator_max(segmented_brackets), NULL);
	while (segmented_brackets[t + 1])
	{
		new_line = ft_strjoin_free(new_line, segmented_brackets[t + 1]);
		if (!new_line)
			return (ft_liberator_max(segmented_brackets), NULL);
		t++;
	}
	ft_liberator_max(segmented_brackets);
	return (new_line);
}
