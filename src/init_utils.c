/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:43:45 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/04 15:57:26 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// mini->line is freed after each readline before execution
// mini->cmd_table is freed in execution
void	free_mini(t_mini **mini)
{
	ft_free_envp((*mini)->env);
	free((*mini)->exit_code_str);
	free(*mini);
	*mini = NULL;
}

int	exit_minishell(t_mini **mini, int exit_code)
{
	if (exit_code)
		perror("");
	else
		write(1, "exit\n", 5);
	free_mini(mini);
	rl_clear_history();
	if (exit_code)
		printf("memory allocation failure");
	exit (exit_code);
}

void	update_exit_status(t_mini *mini, int exit_status)
{
	char	*str;

	if (mini->exit_code == exit_status)
		return ;
	mini->exit_code = exit_status;
	str = ft_itoa(exit_status);
	if (!str)
		exit_minishell(&mini, -1);
	if (mini->exit_code_str != NULL)
		free(mini->exit_code_str);
	mini->exit_code_str = str;
}

int	input_and_parse(t_mini *mini)
{
	char	*mini_str;
	char	*mini_str_temp;

	mini_str_temp = ft_strjoin("▼・ᴥ・▼ฅ(", mini->exit_code_str);
	mini_str = ft_strjoin(mini_str_temp, ") = minishell = ");
	mini->line = readline(mini_str);
	free(mini_str);
	free(mini_str_temp);
	if (!mini->line)
		exit_minishell(&mini, 0);
	if (!*(mini->line))
	{
		if (g_signal)
			update_exit_status(mini, 130);
		return (free(mini->line), 1);
	}
	add_history(mini->line);
	if (ft_read_line(mini))
		return (free(mini->line), 2);
	free(mini->line);
	return (0);
}

t_mini	*mini_init(char **envp)
{
	t_mini	*mini;

	mini = malloc(sizeof(*mini));
	if (!mini)
		return (perror("mini_init (mini)"), NULL);
	if (init_envp(mini, envp) == 1)
		return (perror("mini_init (mini_env)"), free(mini), NULL);
	mini->exit_code = 0;
	mini->exit_code_str = ft_strdup("0");
	if (!mini->exit_code_str)
		return (perror("mini_init (mini_exit)"), free_mini(&mini), NULL);
	return (mini);
}
