/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:26:48 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/03 15:36:08 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_word_len(const char *line)
{
	int	len;
	int	inquote;

	len = 0;
	if (ft_ismeta(*line))
	{
		if ((*line == '<' || *line == '>') && (*(line + 1)) == *line)
			return (2);
		return (1);
	}
	while (*(line + len))
	{
		if (ft_isquote(*(line + len)))
		{
			inquote = 1;
			while ((*(line + len + inquote)) != (*(line + len)))
				inquote++;
			len += inquote;
		}
		if (ft_ismeta(*(line + len)) || ft_isspace(*(line + len)))
			break ;
		len++;
	}
	return (len);
}

static t_token	*process_token(const char *line, int *word_len)
{
	char	*word;

	*word_len = ft_count_word_len(line);
	word = malloc(*word_len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, line, *word_len + 1);
	return (ft_newtoken(word));
}

static t_token	*create_tokenized_list(const char *line)
{
	t_token	*new;
	t_token	*head;
	int		word_len;

	head = NULL;
	new = NULL;
	word_len = 0;
	while (*line)
	{
		if (ft_isspace(*line))
			line++;
		else
		{
			new = process_token(line, &word_len);
			if (!new)
				return (NULL);
			if (head == NULL)
				head = new;
			else
				ft_addtoken(head, new);
			line += word_len;
		}
	}
	return (head);
}

t_token	*ft_tokenizer(const char *line)
{
	t_token	*head;

	head = NULL;
	if (line[0] == '\0')
	{
		head = ft_newtoken("\0");
		return (head);
	}
	head = create_tokenized_list(line);
	return (head);
}

//READ_LINE:
//check the input
//tokenized words with space or meta characters
//check syntax
//update token->type
//parse quote expansion
//retokenized for string with space
//form token into cmd list for execution
int	ft_read_line(t_mini *mini)
{
	char	*line;
	int		exit;

	line = skip_spaces(mini->line);
	exit = end_of_cmd(*line);
	if (exit)
		return (update_exit_status(mini, exit - 1), 1);
	if (!ft_valid_line(mini->line))
		return (update_exit_status(mini, 2), 2);
	expansion(&mini->line, mini->env, mini->exit_code);
	mini->token_lst = ft_tokenizer(mini->line);
	ft_update_token_type(mini->token_lst);
	if (!ft_valid_syntax_order(mini->token_lst))
		return (ft_token_free_lst(mini->token_lst),
			update_exit_status(mini, 2), 2);
	ft_parsing(mini, mini->token_lst);
	mini->cmd_table = create_cmd_arr(mini->token_lst);
	return (0);
}
