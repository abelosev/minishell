// #include "inc/minishell.h"
// #include "inc/parsing.h"
// #include "inc/exec.h"

// int	main(int ac, char **av, char **envp)
// {
// 	t_list_env	*env;
// 	t_list_env	*env2;

// 	(void)ac;
// 	(void)av[0];
// 	env = get_list(envp);
// 	env2 = check_var(env, "SHLVL=1");
// 	env = check_var(env, "ABC");
// 	// mod_var(env, "OLDPWD", "HOME");
// 	print_env_list(env);
// 	printf("\n\n\n");
// 	print_env_list(env2);
// 	mod_var(&env2, "SHLVL=10");
// 	printf("\n\n\n");
// 	print_env_list(env2);
// 	printf("\n\n\n");
// 	if (!env)
// 		printf("vide");
// 	printf("\n\n\n");
// 	mod_var(&env, "ABC=10");
// 	print_env_list(env);
// 	print_env_list(env);
// 	return (0);
// }