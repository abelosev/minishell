/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:04:50 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/26 18:05:09 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_digit_error(t_group *group)
{
	ft_putstr_err("minishell: exit: ");
	ft_putstr_err(group->cmd[1]);
	ft_putstr_err(": numeric argument required\n");
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

int	ft_exit_user_val(t_group *group)
{
	long long	val;
	int			sign;
	int			len;

	sign = 0;
	if (group->cmd[1][0] == '+' || group->cmd[1][0] == '-')
		sign = 1;
	len = ft_strlen(group->cmd[1]);
	if (len > (19 + sign))
		return (ft_exit_digit_error(group), 2);
	if (len == (19 + sign))
	{
		if (group->cmd[1][0] == '-')
		{
			if (ft_strncmp("9223372036854775808",
					&group->cmd[1][sign], 19) < 0)
				return (ft_exit_digit_error(group), 2);
		}
		else if (ft_strncmp("9223372036854775807",
				&group->cmd[1][sign], 19) < 0)
			return (ft_exit_digit_error(group), 2);
	}
	val = ft_atol(group->cmd[1]) % 256;
	return (val);
}

int	ft_exit(t_group *group, int *code)
{
	int	i;

	*code = 0;
	if (group->cmd[1] == NULL)
		return (*code);
	i = 0;
	if ((group->cmd[1][0] == '-' || group->cmd[1][0] == '+')
			&& group->cmd[1][1] != '\0')
		i = 1;
	while (group->cmd[1][i] != '\0')
	{
		if (!ft_isdigit(group->cmd[1][i]))
			return (ft_exit_digit_error(group), 2);
		i++;
	}
	if (group->cmd[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	return (ft_exit_user_val(group));
}
