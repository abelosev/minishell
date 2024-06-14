#include "../../inc/parsing.h"
#include "../../inc/minishell.h"

// typedef struct s_group
// {
// 	unsigned int flag_fail;
// 	char **cmd;
// 	char *redir_in;
// 	char *redir_out;
// 	char *app_out;
// 	char *app_in;
// 	struct s_group *next;
// } t_group;

char	*ft_heredoc_expand(t_group *group, t_list_env *env)
{
	if()
}



	if (type == DELIMITER_Q || !find_dollar(str))
		return (str);
	hd_expansion(&str, env, old_exit);
	if (!str)
		return (perror("heredoc : reconstruct word "), NULL);
	return (str);
}