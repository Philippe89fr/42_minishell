/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:08:47 by lbenatar          #+#    #+#             */
/*   Updated: 2025/01/31 11:36:44 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Est ce que le char est valide?*/
int	char_is_ok(char c)
{
	if (ft_isalnum(c) && c != '_')
		return (1);
	return (0);
}

int	ft_strlen_table(char **table)
{
	int	i;
	int	j;
	int	tot;

	i = 0;
	tot = 0;
	if (!table)
		return (0);
	while (table[i])
	{
		j = 0;
		while (table[i][j])
			j++;
		tot += j;
		i++;
	}
	return (tot);
}

/*On cherche quel est la position du prochain quote,
	si pas de prochain quote on renvoie 0*/
int	check_next_quote(char *line, int ascii, int i)
{
	int	j;

	j = 0;
	while (line[i + j] && line[i + j] != ascii)
		j++;
	if (!line[i + j])
	{
		return (0);
	}
	return (j);
}

char	*fixe_variable(char *variable)
{
	char	**var_tab;
	char	*variable_copy;
	int		i;

	i = 0;
	var_tab = ft_split(variable, ' ');
	free(variable);
	if (!var_tab)
		return (NULL);
	variable_copy = NULL;
	while (var_tab[i])
	{
		variable_copy = ft_strjoin_free(variable_copy, var_tab[i]);
		if (!variable_copy)
			return (ft_liberator_max(var_tab), NULL);
		if (var_tab[i + 1])
		{
			variable_copy = ft_strjoin_free(variable_copy, " ");
			if (!variable_copy)
				return (ft_liberator_max(var_tab), NULL);
		}
		i++;
	}
	return (ft_liberator_max(var_tab), variable_copy);
}
