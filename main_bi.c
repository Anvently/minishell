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

/// @brief Insert results list in place of argv node. Current argv content
/// is replaced with the content of the first result.
/// @param argv
/// @param results Size is always >= 1.
/// @param next Address of a pointer toward the next element in the list,
/// which is equal to the node following current argv node before merging.
/// @return ```0``` for success. ```errno``` for error.
static int	merge_results(t_list *argv, t_list *results, t_list **next)
{

}

/// @brief Check if given arg contain metacharacter to interpret and if
/// insert every match in the list after arg.
/// @param argv A string list's node
/// @param data
/// @return ```0``` for success. ```errno``` if error.
static int	expand_argv(t_list *arg, t_list **next, t_data *data)
{
	t_list	*results;
	t_list	*word_list;
	char	*arg_str;
	int		err;

	err = 0;
	arg_str = (char *)arg->content;
	if (t_word_parse(arg_str, &word_list, &data))
		return (error(errno, "parsing word"));
	if (t_word_concat_dup(word_list))
	{
		ft_lstclear(&word_list, t_word_free);
		return (error(errno, "concatenating word"));
	}
	ft_lstprint(word_list, t_word_print);
	results = NULL;
	err = t_word_interpret(word_list, &results);
	if (!err)
		err = merge_results(arg, results, next);
	if (!err)
		ft_lst_str_print(results);
	ft_lstclear(&results, free);
	ft_lstclear(&word_list, t_word_free);
	return (err);
}

/// @brief Check metacharacters for every node of argv list and insert
/// all matches in the list.
/// @param argv first element of argv (which is the name of the command)
/// is not checked.
/// @param data
/// @return ```0``` for success. ```errno``` if error
static int	interpret_argv(t_list *argv, t_data *data)
{
	if (argv)
		argv = argv->next;
	while (argv)
	{
		if (check_parenthesis(argv, data))
			return (errno);
		else
			argv = argv->next;
		if (argv && expand_arg(argv, &argv, data))
			return (errno);
	}
	return (0);
}

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
