#include <libft.h>
#include <minishell.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

/* int	main(void)
{
	char	*name = ft_substr("=test", 0, 0);
	printf("%s", name);
	return (0);
} */

static int	update_argv(char ***argv, t_data *data)
{
	t_list	*arg_list;

	arg_list = ft_strstolst(*argv);
	if (!arg_list)
		return (errno);
	if (interpret_argv(arg_list, data))
	{
		ft_lstclear(&arg_list, free);
		return (errno);
	}
	ft_free_strs(*argv);
	*argv = ft_lsttostrs(arg_list);
	ft_lstclear(&arg_list, free);
	if (!*argv)
		return (errno);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	**strs;
	char	*line;
	t_data	data;

	(void) argc;
	(void) argv;
	data.exit_status = 0;
	data.env = env_copy(env, ft_strslen(env));
	if (!data.env)
		return (-1);
	while ((line = readline("minishell: ")))
	{
		add_history(line);
		strs = ft_split(line, ' ');
		if (!strs) {
			free(line);
			return (-1);
		}
		if (update_argv(&strs, &data))
		{
			free(line);
			free_data(0, &data);
			rl_clear_history();
			ft_free_strs(strs);
			exit(errno);
		}
		if (!ft_strcmp(strs[0], "export"))
			printf("status = %d\n", builtin_export(strs, &data.env));
		else if (!ft_strcmp(strs[0], "env"))
			printf("status = %d\n", builtin_env(data.env));
		else if (!ft_strcmp(strs[0], "echo"))
			printf("status = %d\n", builtin_echo(strs));
		else if (!ft_strcmp(strs[0], "exit"))
		{
			free(line);
			free_data(0, &data);
			rl_clear_history();
			builtin_exit(strs);
		}
		else if (!ft_strcmp(strs[0], "unset"))
			printf("status = %d\n", builtin_unset(strs, &data.env));
		else if (!ft_strcmp(strs[0], "pwd"))
			printf("status = %d\n", builtin_pwd());
		else if (!ft_strcmp(strs[0], "cd"))
			printf("status = %d\n", builtin_cd(strs, &data.env));
		free(line);
		ft_free_strs(strs);
	}
	return (free_data(0, &data));
}
