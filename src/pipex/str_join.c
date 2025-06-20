/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:41:49 by prambaud          #+#    #+#             */
/*   Updated: 2025/01/21 14:42:17 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join5(char *s1, char *s2, char *conc)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	while (s1[i])
	{
		conc[i] = s1[i];
		i++;
	}
	while (s2[t])
	{
		conc[i + t] = s2[t];
		t++;
	}
	free(s1);
}

char	*ft_strjoin5(char *s1, char *s2)
{
	char	*conc;
	int		t;
	int		i;

	i = 0;
	t = 0;
	while (s1[i])
		i++;
	while (s2[t])
		t++;
	conc = (char *)malloc((t + i + 1) * sizeof(char));
	if (!conc)
		return (NULL);
	conc[t + i] = '\0';
	join5(s1, s2, conc);
	return (conc);
}
