/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:01:41 by lbenatar          #+#    #+#             */
/*   Updated: 2025/02/11 15:28:33 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen4(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	join7(char *line, char *buf, char *conc)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	while (line[i])
	{
		conc[i] = line[i];
		i++;
	}
	while (buf[t])
	{
		conc[i + t] = buf[t];
		t++;
	}
	conc[i + t] = '\0';
}

char	*ft_strjoin7(char *line, char *buf)
{
	char	*conc;
	int		j;

	if (!line)
	{
		line = (char *)malloc(sizeof(char) * 1);
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	j = (ft_strlen(line) + ft_strlen4(buf) + 1) * sizeof(char);
	conc = (char *)malloc(j);
	if (!conc)
	{
		free(line);
		return (NULL);
	}
	join7(line, buf, conc);
	free(line);
	return (conc);
}

char	*ft_strchr8(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (unsigned char)c && s[i])
		return ((char *)&s[i]);
	return (NULL);
}

int	get_here_doc_false_input(t_cmd *lst_cmd, t_pipex *pipex)
{
	char	*instructions;
	int		i;

	i = 0;
	while (i < lst_cmd->count_here_doc - 1)
	{
		instructions = get_here_doc_input(lst_cmd->limiters[i], pipex);
		if (!instructions)
			return (-1);
		free(instructions);
		i++;
	}
	return (0);
}
