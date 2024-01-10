#include <libft.h>
#include <minishell.h>
#include <readline/readline.h>
#include <errno.h>

/* int	main(void)
{
	char	*name = ft_substr("=test", 0, 0);
	printf("%s", name);
	return (0);
} */

int	main(int argc, char **argv, char **env)
{
	char	**env_cop;
	char	**strs;
	char	*line;

	(void) argc;
	(void) argv;
	env_cop = env_copy(env, ft_strslen(env));
	if (!env_cop)
		return (-1);
	while ((line = readline("minishell: ")))
	{
		strs = ft_split(line, ' ');
		if (!strs) {
			free(line);
			return (-1);
		}
		if (!ft_strcmp(strs[0], "export"))
			printf("status = %d\n", builtin_export(strs, &env_cop));
		else if (!ft_strcmp(strs[0], "env"))
			printf("status = %d\n", builtin_env(env_cop));
		else if (!ft_strcmp(strs[0], "echo"))
			printf("status = %d\n", builtin_echo(strs));
		else if (!ft_strcmp(strs[0], "exit"))
		{
			free(line);
			ft_free_strs(env_cop);
			rl_clear_history();
			builtin_exit(strs);
		}
		else if (!ft_strcmp(strs[0], "unset"))
			printf("status = %d\n", builtin_unset(strs, &env_cop));
		else if (!ft_strcmp(strs[0], "pwd"))
			printf("status = %d\n", builtin_pwd());
		else if (!ft_strcmp(strs[0], "cd"))
			printf("status = %d\n", builtin_cd(strs, &env_cop));
		free(line);
		ft_free_strs(strs);
	}
	return (0);
}
