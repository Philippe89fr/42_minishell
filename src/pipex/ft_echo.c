/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:15:34 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/03 13:19:07 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*check si l arg est valide*/
int	echo_valid_arg(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j])
		j++;
	if (str[i] == '-')
		i++;
	while (str[i] == 'n')
		i++;
	if (i != j || i == 1)
		return (0);
	return (1);
}

/*On regarde si la commande est echo puis on regarde si
les arguments sont valide (eg
	-nnnn, -n etc.).
si c'est le cas, echo_arg est le dernier des arguments
*/

char	*echo_arg2(t_token *current, char *echo_arg)
{
	if (current->type == ARG && (current->prev->type == CMD
			|| current->prev->type == ARG))
	{
		if (echo_arg)
		{
			echo_arg = ft_strjoin_free(echo_arg, " ");
			if (!echo_arg)
				return (malloc_fail(), NULL);
		}
		echo_arg = ft_strjoin_free(echo_arg, current->str);
		if (!echo_arg)
			return (malloc_fail(), NULL);
	}
	return (echo_arg);
}

char	*echo_arg3(t_cmd *lst_cmd, char *echo_arg, int i)
{
	if (i == 0)
	{
		echo_arg = ft_strjoin_free(echo_arg, "\n");
		if (!echo_arg)
			return (malloc_fail(), NULL);
	}
	if (echo_arg)
		lst_cmd->echo_arg_malloc = 1;
	return (echo_arg);
}

char	*echo_arg(t_cmd *lst_cmd, t_token *lst_token, int i)
{
	t_token *(current) = lst_token;
	char *(echo_arg) = NULL;
	if (ft_strncmp(current->str, "echo", 5))
		return (NULL);
	current = current->next;
	while (current && current->type != PIPE && !(current->type == ARG
			&& !echo_valid_arg(current->str) && (current->prev->type == CMD
				|| current->prev->type == ARG)))
	{
		if (echo_valid_arg(current->str))
			i++;
		current = current->next;
	}
	while (current && current->type != PIPE)
	{
		echo_arg = echo_arg2(current, echo_arg);
		if (!echo_arg)
			return (NULL);
		current = current->next;
	}
	echo_arg = echo_arg3(lst_cmd, echo_arg, i);
	return (echo_arg);
}

/*imprime avec ou sans \n en fonction du nombre d argument*/
void	ft_echo(t_cmd *lst_cmd)
{
	if (ft_strncmp(lst_cmd->echo_arg, "", 1) == 10)
	{
		ft_printf("\n");
		return ;
	}
	else
		ft_printf("%s", lst_cmd->echo_arg);
}
