/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:14:27 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/01 10:14:30 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_syntax_err(t_token *err)
{
	char	*token;
	char	*err_msg;

	token = "newline";
	err_msg = "minishell: Syntax error near unexpected token";
	if (err)
		token = err->word;
	printf("%s `%s'\n", err_msg, token);
}

// RULES :
// Pipes must be preceeded and followed by at least one Argument
// Input Redirection must be followed by an Input File
// Here Tag must be followed by a DELIMITER
// Output Redirection must be followed by an Output File
// Append Redirection must be followed by an Append File
// LOGIC :
// Check until and including NULL node
// If nothing preceeding, must be ARG or REDIR (not PIPE)
// If ARG preceeding, can be anything
// If PIPE preceeding, must be ARG or REDIR (not PIPE)
// If REDIR preceeding, must be ARG
// If end reached, previous must not be PIPE or REDIR)

int	ft_valid_syntax_order(t_token *current)
{
	t_token	*prev;

	if (current->next == NULL && current->type == ARG)
		return (1);
	if (current->type == PIPE)
		return (print_syntax_err(current), 0);
	while (current)
	{
		prev = current;
		current = current->next;
		if (!current)
			break ;
		if (prev->type == PIPE && current->type == PIPE)
			break ;
		if (prev->type > PIPE)
		{
			if (current->type != ARG)
				break ;
		}
	}
	if (prev->type > ARG)
		return (print_syntax_err(current), 0);
	return (1);
}
