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

/* static int	update_argv(char ***argv, t_data *data)
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
} */

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	data;

	(void) argc;
	data.exit_status = 0;
	data.exe_path = ft_strdup(argv[0]);
	if (!data.exe_path)
		exit(1);
	data.env = env_copy(env, ft_strslen(env));
	data.pipe_list = NULL;
	if (!data.env)
		return (-1);
	while ((line = readline("minishell: ")))
	{
		add_history(line);
		if (parse_line(&data.pipe_list, line))
		{
			free(line);
			return (free_data(1, &data));
		}
		printf("status = %d\n", exec_prompt(data.pipe_list, &data));
		ft_lstclear(&data.pipe_list, free_t_pipe);
		free(line);
	}
	return (free_data(0, &data));
}
