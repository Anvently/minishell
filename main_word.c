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
	char	*line;
	t_list	*word_list;
	t_list	*results;
	t_data	data;

	(void) argc;
	(void) argv;
	data.exit_status = 0;
	data.env = env_copy(env, ft_strslen(env));
	if (!data.env)
		return (-1);
	while ((line = readline("minishell: ")))
	{
		if (t_word_parse(line, &word_list, &data))
			exit(error(errno, "parsing word"));
		if (t_word_concat_dup(word_list))
			exit(error(errno, "concatenating word"));
		ft_lstprint(word_list, t_word_print);
		results = NULL;
		if (!t_word_interpret(word_list, &results))
			ft_lst_str_print(results);
		ft_lstclear(&results, free);
		ft_lstclear(&word_list, t_word_free);
		free(line);
	}
	return (free_data(0, &data));
}
