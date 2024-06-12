/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 09:21:12 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/01 09:21:35 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_arg_amnt(t_token *tokens)
{
	int		word_count;
	t_token	*t;

	t = tokens;
	word_count = 0;
	while (t)
	{
		if (t->type == ARG)
			word_count++;
		t = t->next;
	}
	return (word_count);
}

char	**ft_make_args(t_token *tokens)
{
	int		arg_amnt;
	char	**args;
	t_token	*t;
	int		i;

	arg_amnt = ft_get_arg_amnt(tokens);
	args = malloc(sizeof(char *) * (arg_amnt + 1));
	if (!args)
		return (ft_error(NULL, 0, 1), NULL);
	i = 0;
	t = tokens;
	while (t)
	{
		if (t->type == ARG)
		{
			args[i] = ft_strdup(t->word);
			if (!args[i])
				return (ft_error(NULL, 0, 1),
					ft_free_char_vector_index(args, (i - 1)), NULL);
			i++;
		}
		t = t->next;
	}
	return (args[arg_amnt] = NULL, args);
}
