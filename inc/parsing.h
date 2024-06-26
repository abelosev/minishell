/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:57:38 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/26 17:57:41 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

////////////////// STRUCTS //////////////////

typedef enum s_tokenType
{
	WORD,
	REDIR_IN,
	REDIR_OUT,
	APP_IN,
	APP_OUT,
	PIPE
}	t_tokenType;

//quotes_remove

typedef struct s_remove
{
	int	i;
	int	k;
	int	len;
}	t_remove;

//list of tokens

typedef struct s_tokens
{
	t_tokenType		type;
	char			*value;
	struct s_tokens	*next;
}	t_tokens;

//expand tokenizer

typedef struct s_tokenizer
{
	int		len;
	int		i;
	int		k;
	char	*new;
}	t_tokenizer;

//parser struct 

typedef struct s_parser
{
	char		**token_tab;
	char		*line;
	t_tokens	*token_list;
}	t_parser;

////////////////// FONCTIONS //////////////////

//lexer && parser
void		print_token_list(t_tokens *list);
void		invalid_group(t_group *group, int flag);
int			syntax_pb(t_tokens *list);
char		*get_hd_delimiter(t_tokens *list);
t_parser	*create_init_p(void);
t_tokens	*lexer(char **token_tab);
t_group		*get_group_list(t_tokens *list, t_list_env *env);
t_group		*create_init_group(void);
t_group		*get_group(t_tokens *list, t_list_env *env);
t_group		*create_init_group(void);
t_main		*create_init_m(t_parser *p);

//quotes && expand
int			delimiter_nb(char *str);
int			quotes_ok(char **str);
int			spaces_nb(char *str);
int			is_meta(char *str);
char		*ft_itoa(int n);
char		**spaces_between_quotes(char ***tab);
char		*no_quotes(char *str, char c);
char		*add_spaces(char **tmp);
char		*temp_tokenizer(char *str);
char		*no_quotes(char *str, char c);
char		*with_28(char **str);
char		*ft_expand(char *str, t_list_env *env, int *code);
char		*quotes_expand(char *str, t_list_env *env, int *code);
char		*expanded_token(char *str, t_list_env *env);
char		*no_null(void);
t_tokenizer	*init_data(char *s);
void		between_single(t_tokenizer *d, char *s);
void		before_expand_or_special(t_tokenizer *d, char *s);

//сheck cmd and files
int			only_spaces(char *str);
int			is_folder(char *line);
int			cmd_check(char **str, t_list_env *env);
int			get_files(t_tokens *list, t_group *group);
char		**get_cmd_tab(t_tokens *list);
void		create_file(char *str);
void		permission_pb_msg(char *str);
void		existence_pb_msg(char *str);

//free
void		free_tokens(t_tokens *list);
void		free_t_parser(t_parser *p);

//outils
void		print_tab(char **tab, int fd);
void		print_env_list(t_list_env *list, int fd);
void		print_group(t_group *group);
int			is_special(char c);
char		**ft_split1(char *str, int flag);
char		*from_tab_to_line(char **tab);
void		ft_putstr_err(char *str);
void		ft_putstr_fd(char *str, int fd);
void		print_group_list(t_group *group);

#endif
