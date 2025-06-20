/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:55:07 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/13 15:13:15 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_var;

// Routine  SIGINT // ctrl-c displays a new prompt on a new line
void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		if (g_var != 3)
			write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g_var != 2 && g_var != 3 && g_var != 4)
			rl_redisplay();
		g_var = 1;
	}
}

/* Routine  SIGQUIT // ctrl-D exits the shell.
>> renvoie un EOF que l on traite dans readline ou GNL*/

// Routine  SIGQUIT // ctrl-\ does nothing
void	sigquit_handler(int signal)
{
	if (signal == SIGQUIT)
	{
		if (!g_var || g_var == 2)
		{
			ft_printf("ici\n");
			return ;
		}
		if (g_var != 2 && g_var && g_var != 3)
		{
			write(2, "Quit (core dumped)\n", 19);
			rl_on_new_line();
			rl_replace_line("", 0);
			if (g_var != 4)
				rl_redisplay();
			g_var = 1;
		}
	}
	return ;
}

void	sigquit_handler5(int signal)
{
	if (signal == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_var = 1;
	}
	return ;
}

/* creation des redirection des signaux pour faire ce que l on veut
bzero sert a initialiser les structures
chaque handler doit donner la nouvelle action du signal*/
int	set_signal_action(void)
{
	struct sigaction	signal_sigint;
	struct sigaction	signal_sigquit;

	bzero(&signal_sigint, sizeof(signal_sigint));
	bzero(&signal_sigquit, sizeof(signal_sigquit));
	signal_sigint.sa_handler = &sigint_handler;
	signal_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signal_sigquit, NULL);
	if (sigaction(SIGINT, &signal_sigint, NULL) == 0)
		return (0);
	return (0);
}

int	set_signal_action1(void)
{
	struct sigaction	signal_sigquit;

	bzero(&signal_sigquit, sizeof(signal_sigquit));
	signal_sigquit.sa_handler = &sigquit_handler5;
	sigaction(SIGQUIT, &signal_sigquit, NULL);
	return (0);
}
