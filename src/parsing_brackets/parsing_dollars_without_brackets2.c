/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollars_without_brackets2.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:08:56 by lbenatar          #+#    #+#             */
/*   Updated: 2025/01/22 14:26:54 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_line(char *line, int i)
{
	if (line[i] && line[i] == 34)
	{
		if (line[i + 1] && line[i + 1] == 34)
			return (1);
	}
	if (line[i] && line[i] == 39)
	{
		if (line[i + 1] && line[i + 1] == 39)
			return (1);
	}
	if (line[i] && (line[i] == 34 || line[i] == 39))
	{
		if (check_next_quote(line, line[i], i + 1))
			return (check_next_quote(line, line[i], i + 1));
	}
	return (0);
}

char	*get_part_with_brackets(char *line, int i)
{
	char	*part_with_brackets;
	int		j;
	int		ref;

	part_with_brackets = (char *)malloc(sizeof(char) * (check_next_quote(line,
					line[i], i + 1) + 3));
	if (!part_with_brackets)
		return (NULL);
	j = 0;
	ref = line[i];
	part_with_brackets[j] = line[i];
	j++;
	while (line[i + j] != ref)
	{
		part_with_brackets[j] = line[i + j];
		j++;
	}
	part_with_brackets[j] = line[i + j];
	j++;
	part_with_brackets[j] = '\0';
	return (part_with_brackets);
}

char	*get_part_without_dollars2(char *line, int i)
{
	int		j;
	char	*line_cut;

	j = i;
	while (line[i] && !check_line(line, i) && (!line[i + 1] || line[i] != '$'
			|| !char_is_ok(line[i + 1])))
		i++;
	line_cut = (char *)malloc(sizeof(char) * (i - j + 1));
	if (!line_cut)
		return (NULL);
	i = 0;
	while (line[j] && !check_line(line, j) && (!line[j + 1] || line[j] != '$'
			|| !char_is_ok(line[j + 1])))
	{
		line_cut[i] = line[j];
		j++;
		i++;
	}
	line_cut[i] = '\0';
	return (line_cut);
}
