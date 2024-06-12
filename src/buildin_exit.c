/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 09:14:21 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/01 09:14:25 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_cmd_amnt(t_cmd **cmd_list)
{
	int	i;

	i = 0;
	while (cmd_list[i] != NULL)
		i++;
	return (i);
}

void	ft_exit_digit_error(char **args)
{
	write(2, "minishell: exit: ", 17);
	write(2, args[1], ft_strlen(args[1]));
	write(2, ": numeric argument required\n", 28);
}

long long	ft_atol(char *a)
{
	long long	l;
	int			sign;

	l = 0;
	sign = 1;
	if (!ft_strncmp("-9223372036854775808", a, 100))
		return (LLONG_MIN);
	if (*a == '-' || *a == '+')
	{
		if (*a == '-')
			sign = -1;
		++a;
	}
	while (*a)
	{
		if (l > LLONG_MAX / 10
			|| (l == LLONG_MAX / 10 && (*a - '0') > LLONG_MAX % 10))
			break ;
		l = l * 10 + (*a - '0');
		++a;
	}
	return (sign * l);
}

int	ft_exit_user_val(char **args)
{
	long long	val;
	int			sign;
	int			len;

	sign = 0;
	if (args[1][0] == '+' || args[1][0] == '-')
		sign = 1;
	len = ft_strlen(args[1]);
	if (len > (19 + sign))
		return (ft_exit_digit_error(args), 2);
	if (len == (19 + sign))
	{
		if (args[1][0] == '-')
		{
			if (ft_strncmp("9223372036854775808", &args[1][sign], 19) < 0)
				return (ft_exit_digit_error(args), 2);
		}
		else if (ft_strncmp("9223372036854775807", &args[1][sign], 19) < 0)
			return (ft_exit_digit_error(args), 2);
	}
	val = ft_atol(args[1]);
	val %= 256;
	return (val);
}

int	ft_exit(char **args, t_cmd **cmd_list, int j)
{
	int	i;

	if (j == 0 && ft_get_cmd_amnt(cmd_list) == 1)
		write(1, "exit\n", 5);
	if (args[1] == NULL)
		return (cmd_list[j]->old_exit);
	i = 0;
	if ((args[1][0] == '-' || args[1][0] == '+') && args[1][1] != '\0')
		i = 1;
	while (args[1][i] != '\0')
	{
		if (!ft_isdigit(args[1][i]))
			return (ft_exit_digit_error(args), 2);
		i++;
	}
	if (args[2] != NULL)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	return (ft_exit_user_val(args));
}
